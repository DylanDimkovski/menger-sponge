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

class Camera
{
public:
    void init();
    void draw();
    void done();
    void updateView();

    glm::mat4 view;

protected:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
};
