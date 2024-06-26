#ifndef UIEDITOR_EDITORBASE_H
#define UIEDITOR_EDITORBASE_H

#include "../ImGuiBase.h"
#include <iostream>
#include <random>
#include <chrono>
#include "../stats.hpp"
#include <map>

#define SetCentered(elemSize) { auto xWindow = ImGui::GetWindowSize().x; \
    ImGui::SetCursorPosX((xWindow - elemSize) / 2); }

static const char tryby[] = "Trening\0Zawody\0";

static const char* fontNames[] = {"Roboto", "Comic", "Fjalla", "Lora", "Playwrite" };
static const float fontPrices[] = {0, 50, 40, 30, 20};

static const char* colorNames[] = {"Czerwony", "Zielony", "Niebieski", "Ciemny", "Jasny"};
static const float colorPrices[] = {30, 30, 30, 0, 20};

class GameBase : public ImGuiBase{
public:
    enum Difficulty {
        DIFF_EASY = 0x0,
        DIFF_MEDIUM,
        DIFF_HARD,
    };
    enum Stage {
        MENU = 0x0,
        LOADING,
        INGAME,
        GAME_OVER,
        STATS,
        SETTINGS,
    };
    enum GameMode {
        TIME,
        SCORE,
    };

    enum Color {
        RED,
        GREEN,
        BLUE,
        DARK,
        LIGHT
    };
    
    GameBase() : mCurrentDifficulty(DIFF_EASY), mCurrentStage(MENU), mCurrentIndex(0), mReset(false), mGameMode(TIME), mTimeLeft(0) {}

    static inline GameBase* GetInstance() { return sInstance; }

    void Init(GLFWwindow * window, const char * glsl_version) override;
    void Update() override;

    void SetDifficulty(Difficulty difficulty) { this->mCurrentDifficulty = difficulty; }
    void LoadGame();

    ImVec4 GetCurrentColorValue() { return mColorValues[this->mCurrentColor]; }

    float AddMoneyAfterGame();
    void SpendMoney(float SpentMoney) { this->mMoney -= SpentMoney; };
    void UnlockColor(std::size_t ColorIndex) { this->mIfUnlockedColor[ColorIndex] = true; }
    void UnlockFont(std::size_t FontIndex) { this->mIfUnlockedFont[FontIndex] = true; }
    void SaveMoney();
    void LoadMoney();
private:
    void RenderMainBar();
    void RenderViewPort();
    void RenderMenu();
    void UpdateGame();
    void RenderGame();
    void RenderGameOver();
    void RenderSettings();
    void RenderStats();
    void NextWord();

    const int requiredScore = 10;
    const long long timeModeTime = 20000; //ms

    void Setup(std::vector<std::string>& stringDict, ...);

    static GameBase* sInstance;


    Difficulty mCurrentDifficulty;
    GameMode mGameMode;
    Stage mCurrentStage;
    std::string mCurrentWord;
    int mCurrentIndex;
    Comparator mComp;

    int mDictSize;
    std::vector<std::string> mCurrentDict;
    std::default_random_engine mRng;

    long long mCurrentTime;
    long long mLastTime;
    char mBuffer[0x70];

    bool mReset = false;
    bool mReset2 = false;
    uint32_t mScore;
    long long mTimeLeft;

    std::vector<ImFont*> mFonts;
    int mCurrentFont = 0;
    int mLastFont = 0;
    std::map<Color, ImVec4> mColorValues = {
            {RED, {1.0f, 0.0f, 0.0f, 1.0f}},
            {GREEN, {0.0f, 1.0f, 0.0f, 1.0f}},
            {BLUE, {0.0f, 0.0f, 1.0f, 1.0f}},
            {DARK, {0.1f, 0.1f, 0.1f, 1.0f}},
            {LIGHT, {1.0f, 1.0f, 1.0f, 1.0f}},
    };
    float mMoney = 100;
    Color mCurrentColor = DARK;
    Color mLastColor = DARK;
    std::vector<bool> mIfUnlockedColor = {false, false, false, true, false};
    std::vector<bool> mIfUnlockedFont = {true, false, false, false, false};

    bool mAddMoneyOnce = true;
    float mAddedMoney = 0;
};

#endif //UIEDITOR_EDITORBASE_H
