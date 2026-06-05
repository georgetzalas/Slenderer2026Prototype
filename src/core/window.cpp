#include <core/window.h>

Core::Window& Core::Window::GetInstance()
{
    static Window window;
    return window;
}

Core::Window::Window()
    :width(WIDTH), height(HEIGHT), title(TITLE)
{

}

void Core::Window::ErrorCallback(int error, const char* description)
{
    std::cerr << "[GLFW ERROR] " << description << std::endl;
}

void Core::Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Core::Window::GetInstance().SetWidth(width);
    Core::Window::GetInstance().SetHeight(height);
}

void Core::Window::Init()
{
    glfwSetErrorCallback(Core::Window::ErrorCallback);

    if(!glfwInit())
    {
        std::cerr << "[GLFW ERROR] Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(!window)    
    {
        std::cerr << "[GLFW ERROR] Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Core::Window::WindowSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[GLFW ERROR] Failed to initialize GLAD" << std::endl;
    }
}

bool Core::Window::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void Core::Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Core::Window::PollEvents()
{
    glfwPollEvents();
}

int Core::Window::GetWidth()
{
    return width;
}

int Core::Window::GetHeight()
{
    return height;
}

void Core::Window::SetWidth(int width)
{
    this->width = width;
}

void Core::Window::SetHeight(int height)
{
    this->height = height;
}

std::string& Core::Window::GetTitle()
{
    return title;
}

void Core::Window::Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}