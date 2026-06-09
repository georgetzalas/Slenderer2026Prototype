#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <cstdint>
#include <memory>
#include <string>

typedef uint32_t Index;
typedef uint64_t ID;

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
    ID id;
    int width;
    int height;
    int channels;
    u_char* data;
};

struct Material
{
    Texture* albedo;
    Texture* specular;
    Texture* roughness;
    Texture* normal;
};

struct Mesh
{
    ID id;
    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    Material material;
};

struct Model
{
    ID id;
    std::string name;
    std::string path;
    std::vector<Mesh> meshes;
};