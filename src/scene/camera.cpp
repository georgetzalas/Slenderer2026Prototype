#include "camera.h"

Camera::Camera(glm::vec3 from, glm::vec3 up)
{
    this->_up = up;
    this->from = from;
    this->to = glm::vec3(0.0f, 0.0f, -1.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->zoom = 45.0f;

    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(from, from + to, _up);
}

float Camera::GetZoom()
{
    return zoom;
}

void Camera::ProcessKeyboard(Direction direction)
{
	if(direction == Direction::FORWARD)
	{
		from += to * SPEED;
	}	

	if(direction == Direction::BACK)
	{
		from -= to * SPEED;
	}

	if(direction == Direction::LEFT)
	{
		from -= right * SPEED;
	}

	if(direction == Direction::RIGHT)
	{
		from += right * SPEED;
	}
}

void Camera::ProcessScroll(bool mouseWheelUp, bool mouseWheelDown)
{
    if(mouseWheelUp)
    {
        zoom--;
    }

    if(mouseWheelDown)
    {
        zoom++;
    }

    if(zoom > 89)
    {
        zoom = 89;
    }

    if(zoom < 1)
    {
        zoom = 1;
    }
}

void Camera::ProcessMouse(float xOffset, float yOffset)
{
    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    yaw += xOffset;
    pitch += yOffset;
	
    if(pitch > 89.0f) pitch = 89.0f;
	if(pitch < -89.0f) pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	to = glm::normalize(newFront);

	right = glm::normalize(glm::cross(_up, -to));
	up = glm::normalize(glm::cross(-to, right));
}

glm::vec3 Camera::GetPosition()
{
    return from;
}