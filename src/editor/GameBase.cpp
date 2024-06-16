#include "GameBase.h"
#include "../frazy.h"
#include "imgui.h"
#include <chrono>
#include "../savegame.h"

GameBase * GameBase::sInstance = nullptr;

ImVector<ImWchar> ranges;
void GameBase::Init(GLFWwindow *window, const char *glsl_version) {
    if(sInstance != nullptr) throw ("Another instance of GameBase already exists!");
    ImGuiBase::Init(window, glsl_version);
    sInstance = this;

    ImGuiIO& io = ImGui::GetIO();
    //io.FontGlobalScale = 2.0f;
    ImFontGlyphRangesBuilder builder;
    builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
    builder.AddText("ąęśćóńłżźĄĘŚĆÓŃŁŻŹ");
    builder.BuildRanges(&ranges);
    io.Fonts->AddFontFromFileTTF("Roboto.ttf", 26.0f, nullptr, ranges.Data);
    memset(this->mBuffer, 0, sizeof(this->mBuffer));
    //ImGui::GetStyle().ScaleAllSizes(2.0f);

    io.IniFilename = NULL;
    io.LogFilename = NULL;
}


void GameBase::Update() {
    //RenderMainBar();
    RenderViewPort();
}

void GameBase::RenderMainBar() {

}

ImGuiWindowFlags baseWindowFlags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;

void GameBase::RenderViewPort() {
    ImGuiViewport * viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags rootWindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    rootWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
/*
    ImGui::Begin("Root", nullptr, rootWindowFlags);
    //DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("Root");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    }

    ImGui::End(); //Root
    */
    switch(this->mCurrentStage){
        case MENU:
            RenderMenu();
            break;
        case INGAME:
            UpdateGame();
            RenderGame();
            break;
        case GAME_OVER:
            RenderGameOver();
            break;
        default:
            break;
    }

}

const char* difficultyLabels[] = {
        "Łatwy",
        "Średni",
        "Trudny"
};

void TextCentered(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);

    char buffer[0x100];
    vsnprintf(buffer, sizeof(buffer), fmt, args);

    auto textSize = ImGui::CalcTextSize(buffer).x;

    SetCentered(textSize);
    ImGui::Text(buffer);
    va_end(args);
}
bool test = true;

void GameBase::RenderGame() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Game", nullptr, baseWindowFlags);

    if(ImGui::Button("Wyjdź")){
        this->mCurrentStage = MENU;
    }

    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3);
    TextCentered(this->mCurrentWord.c_str());

    ImGui::SetCursorPosY( 4*windowSize.y / 9);
    ImVec2 size = {600.f / 1280.0f * windowSize.x, 60.0f / 720.0f * windowSize.y};


    if(!this->mReset) {
        SetCentered(size.x);
        ImGui::PushItemWidth((size.x));
        ImGui::InputText("##1", this->mBuffer, sizeof(this->mBuffer));
        if(this->mReset2) ImGui::SetKeyboardFocusHere(-1);
        ImGui::PopItemWidth();
        this->mReset2 = false;
    }
    else {
        this->mReset = false;
        this->mReset2 = true;
    }
    ImGui::SetCursorPosY( 6*windowSize.y / 9);
    TextCentered("Czas: %.2fs", this->mGameMode == TIME ? (this->mCurrentTime)/1000.0f : (this->mTimeLeft)/1000.0f);
    TextCentered("Wynik: %d", this->mScore);

    ImVec2 buttonSize = ImVec2(200, 50);
    ImVec2 buttonPos = ImVec2(center.x - buttonSize.x / 2, center.y + windowSize.y / 4 - buttonSize.y / 16); // Poprawiony buttonPos
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsMouseHoveringRect(buttonPos, ImVec2(buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y))) {
        this->LoadGame();
    }

    ImGui::SetCursorPos(buttonPos);
    if (ImGui::Button("Reset", buttonSize)) {
        this->LoadGame();
    }
    ImGui::End();

}

void GameBase::UpdateGame() {
    auto time = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    this->mCurrentTime = time - this->mLastTime;
    this->mTimeLeft = timeModeTime - (this->mCurrentTime);
    if(this->mGameMode == SCORE){
        if(this->mTimeLeft <= 0){
            this->mCurrentStage = GAME_OVER;
        }
    }
    if(strcmp(this->mCurrentWord.c_str(), this->mBuffer) == 0){
        this->NextWord();
    }
}

void GameBase::NextWord() {
    this->mReset = true;

    if(this->mCurrentIndex >= (this->mDictSize-1)){
        this->mCurrentIndex = -1;
        std::shuffle(this->mCurrentDict.begin(), this->mCurrentDict.end(), this->mRng);
    }
    this->mScore++;
    if(this->mGameMode == TIME){
        if(this->mScore == requiredScore){
            this->mCurrentStage = GAME_OVER;
        }
    }
    this->mCurrentWord = this->mCurrentDict[++this->mCurrentIndex];

    memset(this->mBuffer, 0, 0x70);
}

void GameBase::RenderMenu() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Test", nullptr, baseWindowFlags);
    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3);
    ImFont* font = ImGui::GetFont();
    TextCentered("Mistrz Klawiatury");

    ImGui::PushItemWidth(600.0f);
    ImGui::SetCursorPosY(4*windowSize.y/9);
    TextCentered("Tryb gry");
    SetCentered(630.0f);
    ImGui::Combo("##tryb1", (int*)&this->mGameMode, tryby);
    ImGui::PopItemWidth();
    ImVec2 buttonSize = {180.0f / 1280.0f * windowSize.x, 60.0f / 720.0f * windowSize.y};
    auto cursor = (windowSize.x - 3 * (buttonSize.x + 30)) / 2;


    ImGui::SetCursorPosY( 5*windowSize.y / 9);
    for(int i = 0; i < 3; i++)
    {
        ImGui::SetCursorPosX(cursor);
        if(ImGui::Button(difficultyLabels[i], buttonSize)){
            this->SetDifficulty((Difficulty)i);
            this->LoadGame();
        }
        if(i < 2) ImGui::SameLine();
        cursor += buttonSize.x + 30;
    }
    ImGui::End();
}
char userName[0x100];
void GameBase::RenderGameOver() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("game_over", nullptr, baseWindowFlags);
    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3);
    TextCentered("Koniec gry!");

    if(this->mGameMode == TIME){
        ImGui::SetCursorPosY( 4*windowSize.y / 9);
        TextCentered("Czas: %.3f", (this->mCurrentTime/1000.0f));
    }
    else if(this->mGameMode == SCORE){
        ImGui::SetCursorPosY( 4*windowSize.y / 9);
        TextCentered("Wynik: %d", this->mScore);
    }
    ImVec2 buttonSize = {180.0f / 1280.0f * windowSize.x, 60.0f / 720.0f * windowSize.y};
    auto cursor = (windowSize.x - buttonSize.x) / 2;
    ImGui::SetCursorPosX(cursor);
    if(ImGui::Button("Menu", buttonSize)){
        this->mCurrentStage = MENU;
    }
    auto s = (windowSize.x - 400) / 2.0f; 
    ImGui::SetCursorPosX(s);
    ImGui::PushItemWidth(300);
    ImGui::InputText("##user", userName, 0x100);
    ImGui::SameLine();
    ImGui::PushItemWidth(100);
    if(ImGui::Button("Zapisz")) {
        std::string userName_s = userName;
        int score = (int) this->mScore;
        save(userName_s, score);
        this->mCurrentStage = MENU;
    }
    ImGui::PopItemWidth();

    ImGui::End();
}

void GameBase::Setup(std::vector<std::string> &stringDict, ...) {
    this->mCurrentStage = GameBase::LOADING;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->mRng = std::default_random_engine(seed);
    this->mCurrentIndex = 0;
    this->mDictSize = stringDict.size();
    this->mCurrentDict = std::vector<std::string>(this->mDictSize);

    for(int i = 0; i < this->mDictSize; i++){
        this->mCurrentDict[i] = stringDict[i];
    }
    std::shuffle(mCurrentDict.begin(), mCurrentDict.end(), this->mRng);
}

void GameBase::LoadGame() {
    this->mCurrentTime = 0;
    this->mReset = false;
    this->mScore = 0;
    this->mLastTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    switch (this->mCurrentDifficulty) {
        case DIFF_EASY:
            this->Setup(easy_phrases);
            break;
        case DIFF_MEDIUM:
            this->Setup(medium_phrases);
            break;
        case DIFF_HARD:
            this->Setup(hard_phrases);
            break;
        default:
            // Opcjonalnie: ustawienie domyślnego poziomu trudności lub obsługa błędu
            this->Setup(easy_phrases);
            break;
    }


    this->mCurrentStage = INGAME;
    this->mCurrentWord = this->mCurrentDict[this->mCurrentIndex];
}



