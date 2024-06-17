#ifndef UIEDITOR_EDITORBASE_H
#define UIEDITOR_EDITORBASE_H

#include "../ImGuiBase.h"
#include "../style.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include "../stats.hpp"

#define SetCentered(elemSize) { auto xWindow = ImGui::GetWindowSize().x; \
    ImGui::SetCursorPosX((xWindow - elemSize) / 2); }

static const char tryby[] = "Trening\0Zawody\0";
static const char fontNames[] = "Roboto\0Comic\0Fjalla\0Lora\0Playwrite\0";
static const char colorNames[] = "Czerwony\0Zielony\0Niebieski\0Ciemny\0Jasny\0";

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
    std::map<Color, ImVec4> mColorValues = {
            {RED, {1.0f, 0.0f, 0.0f, 1.0f}},
            {GREEN, {0.0f, 1.0f, 0.0f, 1.0f}},
            {BLUE, {0.0f, 0.0f, 1.0f, 1.0f}},
            {DARK, {0.1f, 0.1f, 0.1f, 1.0f}},
            {LIGHT, {1.0f, 1.0f, 1.0f, 1.0f}},
    };
    Color mCurrentColor = DARK;
};

#endif //UIEDITOR_EDITORBASE_H
