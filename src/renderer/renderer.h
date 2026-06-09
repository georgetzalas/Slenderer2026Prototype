#pragma once

#include <scene/entity.h>
#include <renderer/types.h>
#include <unordered_map>
#include <scene/camera.h>
#include <shader.h>

class Renderer
{
public:
    static Renderer& GetInstance();

    void Init();
    void Destroy();

    void DrawEntity(Entity* entity, Camera& camera);
    MeshGPU GetOrUploadMeshGPU(Mesh& mesh);
    TextureGPU GetOrUploadTextureGPU(Texture* texture);
    void ClearColorDepth();

private:
    Renderer() = default;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

private:
    std::unordered_map<ID, MeshGPU> meshesGPU;
    std::unordered_map<ID, TextureGPU> texturesGPU;
};