#include "GameBase.h"
GameBase * GameBase::sInstance = nullptr;

void GameBase::Init(GLFWwindow *window, const char *glsl_version) {
    if(sInstance != nullptr) throw ("Another instance of GameBase already exists!");
    ImGuiBase::Init(window, glsl_version);
    sInstance = this;

    ImGuiIO& io = ImGui::GetIO();
    //io.FontGlobalScale = 2.0f;
    io.Fonts->AddFontFromFileTTF("Roboto.ttf", 26.0f);
    //ImGui::GetStyle().ScaleAllSizes(2.0f);

#ifdef _DEBUG
    //io.IniFilename = NULL;
   // io.LogFilename = NULL;
#endif

}

void GameBase::Update() {
    RenderMainBar();
    RenderViewPort();
}

void GameBase::RenderMainBar() {

}

void GameBase::RenderViewPort() {

    ImGuiViewport * viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags rootWindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
    rootWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGui::Begin("Root", nullptr, rootWindowFlags);
    //DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspace_id = ImGui::GetID("Root");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
    }

    ImGui::End(); //Root
}



