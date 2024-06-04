#include "GameBase.h"
#include "../frazy.h"
GameBase * GameBase::sInstance = nullptr;

void GameBase::Init(GLFWwindow *window, const char *glsl_version) {
    if(sInstance != nullptr) throw ("Another instance of GameBase already exists!");
    ImGuiBase::Init(window, glsl_version);
    sInstance = this;

    ImGuiIO& io = ImGui::GetIO();
    //io.FontGlobalScale = 2.0f;
    io.Fonts->AddFontFromFileTTF("Roboto.ttf", 26.0f);
    memset(this->buffer, 0, 0x70);
    //ImGui::GetStyle().ScaleAllSizes(2.0f);

#ifdef _DEBUG
    //io.IniFilename = NULL;
   // io.LogFilename = NULL;
#endif

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
        default:
            break;
    }

}

const char* difficultyLabels[] = {
        "Latwy",
        "Sredni",
        "Trudny"
};

void TextCentered(const std::string& text){
    auto xWindow = ImGui::GetWindowSize().x;
    auto textSize = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((xWindow - textSize) / 2);
    ImGui::Text(text.c_str());
}

bool test = true;

void GameBase::RenderGame() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Game", nullptr, baseWindowFlags);
    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3);
    TextCentered(this->mCurrentWord.c_str());

    ImGui::SetCursorPosY( 4*windowSize.y / 9);
    ImVec2 size = {600.f / 1280.0f * windowSize.x, 60.0f / 720.0f * windowSize.y};

    ImGui::SetCursorPosX((windowSize.x - size.x) / 2);

    ImGui::PushItemWidth((size.x));

    if(test) ImGui::InputText("Input", this->buffer, 0x70);
    else {
        test = true;

    }
    ImGui::SetKeyboardFocusHere(-1);
    ImGui::PopItemWidth();

    ImGui::SetCursorPosY( 6*windowSize.y / 9);
    char textBuffer[0x40];
    snprintf(textBuffer, sizeof(textBuffer), "Czas: %.2f s", ((float)this->mCurrentTime) / 1000.0f);
    TextCentered(textBuffer);

    ImGui::End();

}

void GameBase::UpdateGame() {
    if(strcmp(this->mCurrentWord.c_str(), this->buffer) == 0){
        this->NextWord();
    }
}

void GameBase::NextWord() {
    test = false;
    this->mCurrentWord = this->mCurrentDict[++this->mCurrentIndex];
    memset(this->buffer, 0, 0x70);
    auto time = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    auto diff = time - this->mLastTime;
    this->mCurrentTime += diff;
}

void GameBase::RenderMenu() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f,0.5f));
    ImGui::Begin("Test", nullptr, baseWindowFlags);
    auto windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPosY(windowSize.y / 3);
    TextCentered("Wybierz poziom trudnosci");


    ImGui::SetCursorPosY( 4*windowSize.y / 9);
    ImVec2 buttonSize = {180.0f / 1280.0f * windowSize.x, 60.0f / 720.0f * windowSize.y};
    auto cursor = (windowSize.x - 3 * (buttonSize.x + 30)) / 2;

    for(int i = 0; i < 3; i++)
    {
        ImGui::SetCursorPosX(cursor);
        if(ImGui::Button(difficultyLabels[i], buttonSize)){
            this->SetDifficulty((Difficulty)i);
            this->LoadGame();
        }
        ImGui::SameLine();
        cursor += buttonSize.x + 30;
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

    for(int i = 0; i < this->mDictSize; i++){
        this->mCurrentDict[i] = stringDict[i];
    }
    std::shuffle(mCurrentDict.begin(), mCurrentDict.end(), this->mRng);
}

void GameBase::LoadGame() {
    this->mCurrentTime = 0;
    this->mLastTime = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    this->Setup(phrases);
    this->mCurrentStage = INGAME;
    this->mCurrentWord = this->mCurrentDict[this->mCurrentIndex];
    std::cout << this->mDictSize << std::endl;
    std::cout << this->mCurrentWord << std::endl;
}



