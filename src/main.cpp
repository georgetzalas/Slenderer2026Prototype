#include <iostream>
#include <core/window.h>
#include <core/input.h>
#include <importer/asset_manager.h>
#include <scene/scene.h>
#include <renderer/renderer.h>

int main()
{
    std::cout << "Slenderer 2026" << std::endl;

    Core::Window::GetInstance().Init();
    Core::Input::GetInstance().Init();
    Renderer::GetInstance().Init();

    Model* model = Importer::AssetManager::GetInstance().LoadModel("/home/flektos/Downloads/backpack_obj/backpack.obj");
    
    Scene::Scene scene;
    
    Entity* e1 = scene.AddEntity("E1");
    e1->model = model;
    e1->transformComponent.position = glm::vec3(0.0f, 0.0f, -30.0f);

    while(Core::Window::GetInstance().IsOpen())
    {
        Core::Input::GetInstance().Update();

        scene.Update();
        Renderer::GetInstance().ClearColorDepth();
        scene.Render();

        Core::Window::GetInstance().SwapBuffers();
        Core::Window::GetInstance().PollEvents();
    }

    Renderer::GetInstance().Destroy();
    Core::Input::GetInstance().Destroy();
    Core::Window::GetInstance().Destroy();

    return 0;
}