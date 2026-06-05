#pragma once

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int WIDTH    = 1280;
constexpr int HEIGHT   = 720;
constexpr char TITLE[] = "Slenderer 2026";

namespace Core {
class Window
{
public:
    static Window& GetInstance();
    static void ErrorCallback(int error, const char* description);
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);

    void Init();
    void Destroy();
    bool IsOpen();
    void SwapBuffers();
    void PollEvents();
    int GetWidth();
    int GetHeight();
    std::string& GetTitle();

private:
    Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    void SetWidth(int width);
    void SetHeight(int height);

private:
    int width, height;
    std::string title;
    GLFWwindow* window;
};
};