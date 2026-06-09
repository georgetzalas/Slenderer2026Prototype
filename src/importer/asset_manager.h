#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utils/types.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <utils/util.h>
#include <stb/stb_image.h>
#include <cstdint>

namespace Importer{
class AssetManager
{
public:
    static AssetManager& GetInstance();

    void LoadModel(const std::string& path);
    void LoadTexture(const std::string& path);
    //void LoadShader(const std::string& vertexPath, const std::string& fragmentPath);

private:
    AssetManager() = default;

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);

private:
    Model model;

    std::unordered_map<std::string, std::unique_ptr<Model>> models;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};
};