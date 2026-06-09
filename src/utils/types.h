#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <cstdint>
#include <memory>
#include <string>

typedef uint64_t Index;

struct Vertex
{
    glm::vec3 position;
    glm::vec2 textureCoordinates;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture
{
    int width;
    int height;
    int channels;
    u_char* data;
};

struct Material
{
    Texture* texture;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    Material material;
};


struct Model
{
    std::string name;
    std::string path;
    std::vector<Mesh> meshes;
};