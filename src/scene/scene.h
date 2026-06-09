#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <core/input.h>
#include <scene/camera.h>
#include <scene/entity.h>
#include <utils/types.h>
#include <renderer/renderer.h>

namespace Scene{
class Scene
{
public:
    Scene() = default;

    void Update();
    void Render();

    Entity* AddEntity(const std::string& name);
    Entity* GetEntity(const std::string& name);
    std::vector<Entity*>& GetEntities();
    void RemoveEntity(const std::string& name);

private:
    Camera camera;
    EntityID id = 0;
    std::vector<Entity*> entities;
};
};