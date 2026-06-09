#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float SPEED = 0.5f;
constexpr float SENSITIVITY = 0.1f;

enum class Direction
{
    FORWARD,
    BACK,
    RIGHT,
    LEFT
};

class Camera
{
public:
    Camera(glm::vec3 from = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 GetViewMatrix();
    float GetZoom();
    glm::vec3 GetPosition();

    void ProcessKeyboard(Direction direction);
    void ProcessScroll(bool mouseWheelUp, bool mouseWheelDown);
    void ProcessMouse(float xOffset, float yOffset);
private:
    void UpdateCameraVectors();

private:
    glm::vec3 right, up, forward;
    glm::vec3 from, to;
    glm::vec3 _up;
    float zoom;
    float yaw, pitch;
};