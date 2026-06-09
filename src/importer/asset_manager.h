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
#include <stb_image.h>
#include <cstdint>

namespace Importer{
class AssetManager
{
public:
    static AssetManager& GetInstance();

    Model* LoadModel(const std::string& path);
    Texture* LoadTexture(const std::string& path);
    //void LoadShader(const std::string& vertexPath, const std::string& fragmentPath);

    Model* GetModel(const std::string& name);
    Texture* GetTexture(const std::string& name);

private:
    AssetManager() = default;

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    void ProcessNode(aiNode* node, const aiScene* scene, Model* model);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene, Model* model);
    void ProcessMaterial(aiMesh* mesh, const aiScene* scene, Model* model, Material& material);
private:
    ID modelID    = 0;
    ID meshID     = 0;
    ID textureID  = 0;

    std::unordered_map<std::string, std::unique_ptr<Model>> models;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures;
};
};