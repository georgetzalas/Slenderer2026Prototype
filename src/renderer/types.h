#pragma once

#include <glad/glad.h>

struct MeshGPU
{
    GLuint VAO, VBO, EBO;
};

struct TextureGPU
{
    GLuint id;
};