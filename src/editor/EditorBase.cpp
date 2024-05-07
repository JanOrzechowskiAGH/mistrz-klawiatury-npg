#include "EditorBase.h"
#include "../system/ImageLoader.h"
EditorBase * EditorBase::sInstance = nullptr;

int image_width = 0;
int image_height  = 0;
GLuint myTexture = 0;




void EditorBase::Init(GLFWwindow *window, const char *glsl_version) {
    if(sInstance != nullptr) throw ("Another instance of EditorBase already exists!");
    ImGuiBase::Init(window, glsl_version);
    sInstance = this;

    ImGuiIO& io = ImGui::GetIO();
#ifdef _DEBUG
    //io.IniFilename = NULL;
   // io.LogFilename = NULL;
#endif

    bool ret = ImageLoader::LoadTextureFromFile("C:\\NPG\\mistrz-klawiatury-npg\\mistrz.jpg", &myTexture, &image_width, &image_height);
}



void EditorBase::Update() {
    RenderMainBar();
    RenderViewPort();

//region ConfirmExit

    if(this->confirmingExit)
    {
        bool a = true;
        if(!hasChanges) exit(0);

        if(ImGui::Begin("Confirm Exit", &a, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize))
        {
            ImGui::SetWindowSize(ImVec2(280.0f, 80.0f));
            ImGui::Text("Are you sure you want to exit?");
            if(ImGui::Button("No")){
                this->confirmingExit = false;
            }
            ImGui::SameLine();
            if(ImGui::Button("Yes")){
                exit(0);
            }
            ImGui::End();
        }
        if(!a) this->confirmingExit = false;
//endregion
    }
}

void EditorBase::RenderMainBar() {
    /*
    ImGui::BeginMainMenuBar();

    if(ImGui::BeginMenu("File")){
        ImGui::BeginMenuBar();

        if(ImGui::MenuItem("Open")){

            std::string ret = FileDialogManager::OpenFileDialog("Open File", "BRLYT files (*.brlyt)\0*.brlyt\0");

            if(!ret.empty()) {
                std::cout << ret << std::endl;
            }

        }
        ImGui::MenuItem("Save");
        ImGui::MenuItem("Save as...");
        ImGui::Separator();
        if(ImGui::MenuItem("Exit"))
        {
            this->confirmingExit = true;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
    */
}

bool przycisk = false;
bool demoWindow = false;
float test = 0.0f;
float test2 = 0.0f;
char buffer[64];
float color[4] = {1.0f,1.0f,1.0f,1.0f};

void EditorBase::RenderViewPort() {

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

    ImDrawList* backGround = ImGui::GetBackgroundDrawList();
    backGround->AddImage(reinterpret_cast<ImTextureID>(myTexture), ImVec2(0.0f, 0.0f), ImVec2(viewport->WorkSize.x, viewport->WorkSize.y));

    ImGui::Begin("Test Window", nullptr);

    ImGui::Text("Inne okno");
    ImGui::Checkbox("Demo Window", &demoWindow);
    if(demoWindow){
        ImGui::ShowDemoWindow();
    }
    ImGui::Checkbox("Button", &przycisk);
    if(przycisk)
    {
        ImGui::SliderFloat("Slider", &test, -1.0f, 1.0f);
        ImGui::DragFloat("Drag", &test2, 0.2f, -1.0f, 1.0f);

        ImGui::ColorEdit4("Kolorek", color);

        ImGui::TextColored(ImVec4(color[0],color[1],color[2],color[3]),"This is a text window for testing purposes");
    }

    ImGui::Text("\nRabarbar");
    ImGui::InputText("Input: ", buffer, 64);
    if(strcmp("Rabarbar", buffer) == 0){
        ImGui::Text("Wygral");
    }



    ImGui::End();
}



