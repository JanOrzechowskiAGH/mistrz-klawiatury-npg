#ifndef UIEDITOR_EDITORBASE_H
#define UIEDITOR_EDITORBASE_H

#include "../ImGuiBase.h"
#include <iostream>

class GameBase : public ImGuiBase{
public:
    static GameBase * GetInstance() { return sInstance; }

    void Init(GLFWwindow * window, const char * glsl_version) override;
    void Update() override;
    void MarkChange() { hasChanges = true; }


private:
    void RenderMainBar();
    void RenderViewPort();

    static GameBase * sInstance;
    bool hasChanges = false;
    bool confirmingExit = false;
};

#endif //UIEDITOR_EDITORBASE_H
