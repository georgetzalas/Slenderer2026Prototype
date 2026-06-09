#include <scene/scene.h>

void Scene::Scene::Update()
{
    if(Core::Input::GetInstance().IsKeyboardKeyDown(GLFW_KEY_W))
    {
        camera.ProcessKeyboard(Direction::FORWARD);
    }

    if(Core::Input::GetInstance().IsKeyboardKeyDown(GLFW_KEY_S))
    {
        camera.ProcessKeyboard(Direction::BACK);
    }
    
    if(Core::Input::GetInstance().IsKeyboardKeyDown(GLFW_KEY_A))
    {
        camera.ProcessKeyboard(Direction::LEFT);
    }

    if(Core::Input::GetInstance().IsKeyboardKeyDown(GLFW_KEY_D))
    {
        camera.ProcessKeyboard(Direction::RIGHT);
    }
}

void Scene::Scene::Render()
{
    for(int i=0; i<entities.size(); i++)
    {
        Renderer::GetInstance().DrawEntity(entities[i], camera);
    }
}

Entity* Scene::Scene::AddEntity(const std::string& name)
{
    Entity* entity = new Entity;
    entity->id     = id++;
    entity->name   = name;

    entities.push_back(entity);

    return entity;
}

Entity* Scene::Scene::GetEntity(const std::string& name)
{
    for(int i=0; i<entities.size(); i++)
    {
        if(entities[i]->name == name)
        {
            return entities[i];
        }
    }

    std::cerr << "[SCENE ERROR] Couldnt find entity with name " << name << std::endl;

    return nullptr;
}

std::vector<Entity*>& Scene::Scene::GetEntities()
{
    return entities;
}

void Scene::Scene::RemoveEntity(const std::string& name)
{
    for(auto it=entities.begin(); it!=entities.end(); it++)
    {
        if((*it)->name == name)
        {
            entities.erase(it);
            return;
        }
    }
}