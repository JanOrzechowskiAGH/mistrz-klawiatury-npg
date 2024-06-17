#include "style.hpp"
#include <imgui.h>


void Style::change_curr_font_color(color next_font_color){
    if (curr_font_color_ == next_font_color){
        return;
    }
    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_Text] = font_color_[next_font_color];
}


