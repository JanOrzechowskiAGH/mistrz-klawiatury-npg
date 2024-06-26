#include <iostream>
#include "ImGuiBase.h"
#include "editor/GameBase.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
int main() {
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Mistrz Klawiatury", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw("Unable to context to OpenGL");

    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
    glViewport(0, 0, screen_width, screen_height);

    GameBase myimgui;
    myimgui.Init(window, glsl_version);
    myimgui.LoadMoney();
    ImVec4 CurrentColorValue;
    while (!glfwWindowShouldClose(window)) {
        CurrentColorValue = myimgui.GetCurrentColorValue();
        glfwPollEvents();
        glClearColor(CurrentColorValue.x, CurrentColorValue.y, CurrentColorValue.z, CurrentColorValue.w);
        glClear(GL_COLOR_BUFFER_BIT);
        myimgui.NewFrame();
        myimgui.Update();
        myimgui.Render();
        glfwSwapBuffers(window);
    }
    myimgui.SaveMoney();
    myimgui.Shutdown();

    return EXIT_SUCCESS;
}
