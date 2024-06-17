#ifndef NPG_STYLE_HPP
#define NPG_STYLE_HPP
#include<iostream>
#include <imgui.h>
#include <vector>
#include <map>
typedef enum { red, green, blue} color;
class Style{
public:
    Style(std::vector<ImFont*> fonts): fonts_(std::move(fonts)), curr_font_style_(fonts_[0]){}
    void set_curr_font_style(std::size_t next_font_style) {curr_font_style_ = fonts_[next_font_style];}
    void change_curr_font_color(color);
    ImFont* get_curr_font_style() { return curr_font_style_;}
private:
    std::vector<ImFont*> fonts_;
    std::map<color, ImVec4> font_color_{
            {red, ImVec4(255.0f, 0.0f, 0.0f, 1.00f)},
            {green, ImVec4(0.0f, 255.0f, 0.0f, 1.00f)},
            {blue, ImVec4(0.0f, 0.0f, 255.0f, 1.00f)}
    };
    color curr_font_color_ = red;
    ImFont* curr_font_style_;
};


#endif //NPG_STYLE_HPP
