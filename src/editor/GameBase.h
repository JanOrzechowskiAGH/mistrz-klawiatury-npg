#ifndef UIEDITOR_EDITORBASE_H
#define UIEDITOR_EDITORBASE_H

#include "../ImGuiBase.h"
#include <iostream>
#include <random>

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

    GameBase() : mCurrentDifficulty(DIFF_EASY), mCurrentStage(MENU), mCurrentIndex(0) {}

    static inline GameBase* GetInstance() { return sInstance; }

    void Init(GLFWwindow * window, const char * glsl_version) override;
    void Update() override;

    // __VA_ARGS__ tylko żebym pamiętał by to rozszerzać
    void SetDifficulty(Difficulty difficulty) { this->mCurrentDifficulty = difficulty; }
    void LoadGame();


private:
    void RenderMainBar();
    void RenderViewPort();
    void RenderMenu();
    void UpdateGame();
    void RenderGame();
    void NextWord();

    void Setup(std::vector<std::string>& stringDict, ...);

    static GameBase* sInstance;


    Difficulty mCurrentDifficulty;
    Stage mCurrentStage;
    std::string mCurrentWord;
    int mCurrentIndex;

    int mDictSize;
    std::vector<std::string> mCurrentDict;
    std::default_random_engine mRng;

    long long mCurrentTime;
    long long mLastTime;
    char buffer[0x70];

};

#endif //UIEDITOR_EDITORBASE_H
