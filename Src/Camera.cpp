#include "Camera.h"

void Camera::init()
{
	position = glm::vec3(10.0f, 5.0f, 20.0f);
	front = glm::vec3(-10.0f, -5.0f, -20.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	updateView();
}

void Camera::draw()
{

}

void Camera::done()
{

}

void Camera::updateView()
{
	view = glm::lookAt(position, position + front, up);
}
