#pragma once

#include <GLFW/glfw3.h>
#include <cstdint>
#include <core/window.h>

constexpr int KEYBOARD_KEYS = 1024;
constexpr int MOUSE_KEYS    = 32;

namespace Core{
class Input
{
public:
    static Input& GetInstance();
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void Init();
    void Destroy();
    void Update();
    
    bool IsKeyboardKeyPressed(uint32_t key);
    bool IsKeyboardKeyDown(uint32_t key);

    bool IsMouseKeyPressed(uint32_t key);
    bool IsMouseKeyDown(uint32_t key);

    double GetMousePosX();
    double GetMousePosY();

    double GetMousePosXLastFrame();
    double GetMousePosYLastFrame();

    double GetMouseOffsetX();
    double GetMouseOffsetY();

    bool IsMouseWheelUp();
    bool IsMouseWheelDown();

    int GetYScrollOffset();
    void SetYScrollOffset(int offset);

    void DisableCursor();
    void EnableCursor();

private:
    Input();

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;

private:
    bool keyboardKeysDown[KEYBOARD_KEYS];
    bool keyboardKeysDownLastFrame[KEYBOARD_KEYS];
    bool keyboardKeysPressed[KEYBOARD_KEYS];

    bool mouseKeysDown[MOUSE_KEYS];
    bool mouseKeysDownLastFrame[MOUSE_KEYS];
    bool mouseKeysPressed[MOUSE_KEYS];

    double mousePosX;
    double mousePosY;

    double mousePosXLastFrame;
    double mousePosYLastFrame;

    double mouseOffetX;
    double mouseOffetY;

    bool mouseWheelUp;
    bool mouseWheelDown;

    int yScrollOffset = 0;

};
};