#ifndef UIEDITOR_EDITORBASE_H
#define UIEDITOR_EDITORBASE_H

#include "../ImGuiBase.h"
#include <iostream>
#include <random>
#include <chrono>

#define SetCentered(elemSize) auto xWindow = ImGui::GetWindowSize().x; \
    ImGui::SetCursorPosX((xWindow - elemSize) / 2);

static const char tryby[] = "Trening\0Zawody";

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
    };
    enum GameMode {
        TIME,
        SCORE,
    };
    
    GameBase() : mCurrentDifficulty(DIFF_EASY), mCurrentStage(MENU), mCurrentIndex(0), mReset(false), mGameMode(TIME), mTimeLeft(0) {}

    static inline GameBase* GetInstance() { return sInstance; }

    void Init(GLFWwindow * window, const char * glsl_version) override;
    void Update() override;

    void SetDifficulty(Difficulty difficulty) { this->mCurrentDifficulty = difficulty; }
    void LoadGame();


private:
    void RenderMainBar();
    void RenderViewPort();
    void RenderMenu();
    void UpdateGame();
    void RenderGame();
    void RenderGameOver();
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

    int mDictSize;
    std::vector<std::string> mCurrentDict;
    std::default_random_engine mRng;

    long long mCurrentTime;
    long long mLastTime;
    char mBuffer[0x70];

    bool mReset = false;
    uint32_t mScore;
    long long mTimeLeft;
};

#endif //UIEDITOR_EDITORBASE_H
