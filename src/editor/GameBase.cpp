#include "GameBase.h"
#include "../frazy.h"

#include "imgui.h"
#include "../savegame.h"
#include "../stats.hpp"
#include <string>
#include <sstream>
#include <chrono>

GameBase * GameBase::sInstance = nullptr;

ImVector<ImWchar> ranges;
void GameBase::Init(GLFWwindow *window, const char *glsl_version) {
    if(sInstance != nullptr) throw ("Another instance of GameBase already exists!");
    ImGuiBase::Init(window, glsl_version);
    sInstance = this;
    //io.FontGlobalScale = 2.0f;a
    ImGuiIO& io = ImGui::GetIO();
    //io.FontGlobalScale = 2.0f;
    ImFontGlyphRangesBuilder builder;
    builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
    builder.AddText("ąęśćóńłżźĄĘŚĆÓŃŁŻŹ");
    builder.BuildRanges(&ranges);
    //ImGui::GetStyle().ScaleAllSizes(2.0f);

    ImFont* Roboto = io.Fonts->AddFontFromFileTTF("Roboto.ttf", 28.0f, nullptr, ranges.Data);
    ImFont* Comic = io.Fonts->AddFontFromFileTTF("Comic.ttf", 28.0f, nullptr, ranges.Data);
    ImFont* Fjalla = io.Fonts->AddFontFromFileTTF("Fjalla.ttf", 28.0f, nullptr, ranges.Data);
    ImFont* Lora = io.Fonts->AddFontFromFileTTF("Lora.ttf", 28.0f, nullptr, ranges.Data);
    ImFont* Playwrite = io.Fonts->AddFontFromFileTTF("Playwrite.ttf", 28.0f, nullptr, ranges.Data);
    mFonts = {Roboto, Comic, Playwrite, Fjalla, Lora};
    memset(this->mBuffer, 0, sizeof(this->mBuffer));
    //ImGui::GetStyle().ScaleAllSizes(2.0f);
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

    ImFont* font = this->mFonts[this->mCurrentFont];
    ImGui::PushFont(font);

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    if(this->mCurrentColor == RED || this->mCurrentColor == LIGHT){
        style.Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
        
    }

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
        case STATS:
            RenderStats();
            break;
        case SETTINGS:
            RenderSettings();
            break;
        default:
            break;
    }
    ImGui::PopFont();

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
    //ImGui::PushFont(curr_style.get_curr_font_style());
    ImGui::Text(buffer);
    //ImGui::PopFont();
    va_end(args);
}
bool test = true;

void GameBase::RenderSettings() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Settings", nullptr, baseWindowFlags);

    if(ImGui::Button("Wyjdź")){
        this->mCurrentStage = MENU;
    }

    std::vector<std::string> fontNamesWithPrices;
    for(int i = 0; i < 5; i++) {
        char temp[0x100];
        snprintf(temp, 0x100,"%s (%.2f)", fontNames[i], fontPrices[i]);
        fontNamesWithPrices.emplace_back(this->mIfUnlockedFont[i] ? fontNames[i] : temp);
    }

    const char* charNames[5];
    for(int i = 0; i < 5; i++){
        charNames[i] = fontNamesWithPrices[i].c_str();
    }

    std::vector<std::string> colorNamesWithPrices;
    for(int i = 0; i < 5; i++) {
        char temp[0x100];
        snprintf(temp, 0x100,"%s (%.2f)", colorNames[i], colorPrices[i]);
        colorNamesWithPrices.emplace_back(this->mIfUnlockedColor[i] ? colorNames[i] : temp);
    }

    const char* charColorNames[5];
    for(int i = 0; i < 5; i++){
        charColorNames[i] = colorNamesWithPrices[i].c_str();
    }

    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3 - 25.0f);
    TextCentered("Pieniążki: %0.2f$", this->mMoney);
    ImGui::SetCursorPosY(windowSize.y / 3);
    TextCentered("Sklep");
    SetCentered(630.0f);
    ImGui::PushItemWidth(600.0f);
    ImGui::Combo("Czcionka", &this->mCurrentFont, charNames, 5);
    SetCentered(630.0f);
    ImGui::Combo("Kolor", (int*)&this->mCurrentColor, charColorNames, 5);
    ImGui::PopItemWidth();

    if(!this->mIfUnlockedFont[this->mCurrentFont]){
        if(this->mMoney >= fontPrices[this->mCurrentFont]){
            this->mIfUnlockedFont[this->mCurrentFont] = true;
            this->SpendMoney(fontPrices[this->mCurrentFont]);
        }
        else
            this->mCurrentFont = this->mLastFont;
    }
    this->mLastFont = this->mCurrentFont;

    if(!this->mIfUnlockedColor[this->mCurrentColor]){
        if(this->mMoney >= colorPrices[this->mCurrentColor]){
            this->mIfUnlockedColor[this->mCurrentColor] = true;
            this->SpendMoney(colorPrices[this->mCurrentColor]);
        }
        else
            this->mCurrentColor = this->mLastColor;
    }
    this->mLastColor = this->mCurrentColor;
    ImGui::End();
};

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
    if(ImGui::Button("Sklep")){
        this->mCurrentStage = SETTINGS;
    }

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
        //ImGui::PushFont(style.get_curr_font_style());
        if(ImGui::Button(difficultyLabels[i], buttonSize)){
            this->SetDifficulty((Difficulty)i);
            this->LoadGame();
        }
        //ImGui::PopFont();
        if(i < 2) ImGui::SameLine();
        cursor += buttonSize.x + 30;
    }

    ImGui::SetCursorPosY(2*windowSize.y/3);
    ImGui::SetCursorPosX((windowSize.x - buttonSize.x - 30) / 2);
    if (ImGui::Button("Statystyki", buttonSize)){
        this -> mCurrentStage = STATS;
    }

    ImGui::SetCursorPosY(45.0f);
    ImGui::SetCursorPosX(10.0f);
    ImGui::Text("Pieniążki: %0.2f$", this->mMoney);
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
    float AddedMoney = AddMoneyAfterGame();
    ImGui::SetCursorPosY(7*windowSize.y / 9);
    TextCentered("Zdobyte pieniążki: %.2f$", (AddedMoney));
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
    else if(this->mGameMode == SCORE) {
        auto s = (windowSize.x - 400) / 2.0f;
        ImGui::SetCursorPosX(s);
        ImGui::PushItemWidth(300);
        ImGui::InputText("##user", userName, 0x100);
        ImGui::SameLine();
        ImGui::PushItemWidth(100);
        if (ImGui::Button("Zapisz")) {
            std::string userName_s = userName;
            if(userName_s.size() > 20){
                userName_s = userName_s.substr(0, 20);
            }
            int score = (int) this->mScore;
            save(userName_s, score);
            this->mCurrentStage = MENU;
        }
        ImGui::PopItemWidth();
    }
    ImGui::End();
}

void GameBase::Setup(std::vector<std::string> &stringDict, ...) {
    this->mCurrentStage = GameBase::LOADING;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->mRng = std::default_random_engine(seed);
    this->mCurrentIndex = 0;
    this->mDictSize = stringDict.size();
    this->mCurrentDict = std::vector<std::string>(this->mDictSize);
    this->mReset = true;
    memset(this->mBuffer, 0, sizeof(this->mBuffer));
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


static const char opcje_sort[] = "Liczba gier\0Najwyższy wynik\0Średni Wynik\0";
// Pierwszy raz to robiłem więc sprawdźcie to ale chyba działa
void GameBase::RenderStats() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Stats", nullptr, baseWindowFlags);
    auto windowSize = ImGui::GetWindowSize();

    if(ImGui::Button("Wyjdź")){
        this->mCurrentStage = MENU;
    }

    auto cursor = windowSize.y / 9;
    ImGui::SetCursorPosY( cursor);
    TextCentered("Statystyki");

    TextCentered("Sortuj po:");
    ImGui::SetCursorPosX(  (windowSize.x/5) );
    ImGui::Combo("##sortowanie", (int*)&this->mComp, opcje_sort);

    cursor = 3*windowSize.y / 9;
    ImGui::SetCursorPosY( cursor );
    std::vector<std::string> text = { "Nazwa użytkownika",
                                      "Liczba gier",
                                      "Najwyższy wynik",
                                      "Średni wynik"};
    for (int i = 0; i < 4; ++i) {
        ImGui::SetCursorPosY( cursor);
        ImGui::SetCursorPosX(  ((windowSize.x/16) + i*windowSize.x/4) );
        ImGui::Text(text[i].c_str());
    }

    cursor = 4*windowSize.y / 9;
    ImGui::SetCursorPosY( cursor );
    std::vector<StatsEntry> users = getUsersStats();
    sortStatsEntries(users, mComp);
    for (const auto& user: users){
        std::vector<std::string> user_text = { user.getUsername(),
                                          std::to_string(user.getGameCount()),
                                          std::to_string(user.getHighScore()),
                                          std::to_string(user.getAvgScore()).substr(0, 4)};
        for (int i = 0; i < 4; ++i) {
            ImGui::SetCursorPosY( cursor);
            ImGui::SetCursorPosX(  ((windowSize.x/16) + (i*windowSize.x/4) + 30 ) );
            ImGui::Text(user_text[i].c_str());
        }

        cursor += 30;
    }


    ImGui::End();
}

float GameBase::AddMoneyAfterGame(){
    float AddedMoney;
    if(this->mGameMode == SCORE){
        AddedMoney = (float) this->mScore * (float) (this->mCurrentDifficulty + 1);
    } else{
        AddedMoney = (float) this->mCurrentTime/10000.0f * (float) (this->mCurrentDifficulty + 1);
    }
    this->mMoney += AddedMoney;
    return AddedMoney;
}
