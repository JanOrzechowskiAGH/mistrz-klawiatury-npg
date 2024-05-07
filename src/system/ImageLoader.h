//
// Created by janor on 24.04.2024.
//
#pragma once
#ifndef UIEDITOR_IMAGELOADER_H
#define UIEDITOR_IMAGELOADER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ImageLoader {
public:
    static bool LoadTextureFromFile(const std::string& path, GLuint* out_texture, int* out_width, int* out_height);
};


#endif //UIEDITOR_IMAGELOADER_H
