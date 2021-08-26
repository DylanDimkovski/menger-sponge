#include "Camera.h"

void Camera::init(float width, float height)
{
	this->width = width;
	this->height = height;

	position = glm::vec3(0.0f, 0.0f, 10.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	updateView();
}

void Camera::draw()
{

}

void Camera::done()
{

}

void Camera::mouseMove()
{
    Uint32 buttons;
    int x, y;

    buttons = SDL_GetMouseState(&x, &y);

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    if ((buttons & SDL_BUTTON_LMASK) != 0) {
        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 temp;
        temp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        temp.y = sin(glm::radians(pitch));
        temp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(temp);
    }
}

void Camera::updateProjection()
{
	projection = glm::perspective(glm::radians(60.0f), width / height, 0.01f, 1000.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
}

void Camera::updateView()
{
	view = glm::lookAt(position, position + front, up);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(view));
}
