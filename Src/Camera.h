#pragma once
//-----------------------------------------------------------------------------
// Camera.h
//-----------------------------------------------------------------------------
// Header Code For Camera
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include <glm/ext.hpp>
#include <glad/glad.h>
#include <sdl/SDL.h>

class Camera
{
public:
    void init(float width, float height);

    void updateProjection();
    void updateView();
    void mouseMove();

    float width = 0;
    float height = 0;

    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    bool  firstMouse = true;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0f;
    float lastY = 600.0f / 2.0f;

    float speed = 50.0f;
};
