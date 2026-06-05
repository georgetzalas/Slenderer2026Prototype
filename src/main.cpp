#include <iostream>
#include <core/window.h>

int main()
{
    std::cout << "Slenderer 2026" << std::endl;

    Core::Window::GetInstance().Init();
    
    while(Core::Window::GetInstance().IsOpen())
    {

        int width = Core::Window::GetInstance().GetWidth();
        std::cout << width << std::endl;

        Core::Window::GetInstance().SwapBuffers();
        Core::Window::GetInstance().PollEvents();
    }

    Core::Window::GetInstance().Destroy();

    return 0;
}