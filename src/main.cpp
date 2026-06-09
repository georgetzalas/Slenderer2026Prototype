#include <iostream>
#include <core/window.h>
#include <core/input.h>
#include <importer/asset_manager.h>

int main()
{
    std::cout << "Slenderer 2026" << std::endl;

    Core::Window::GetInstance().Init();
    Core::Input::GetInstance().Init();
    Model* model = Importer::AssetManager::GetInstance().LoadModel("/home/flektos/Downloads/backpack_obj/backpack.obj");
    
    while(Core::Window::GetInstance().IsOpen())
    {
        Core::Input::GetInstance().Update();

        Core::Window::GetInstance().SwapBuffers();
        Core::Window::GetInstance().PollEvents();
    }

    Core::Input::GetInstance().Destroy();
    Core::Window::GetInstance().Destroy();

    return 0;
}