//-----------------------------------------------------------------------------
// Scene.h
//-----------------------------------------------------------------------------
// Header Code For Scene Object
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include "Camera.h"
#include "Cube.h"
#include <glm/ext.hpp>

class Scene
{
public:
    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void done() = 0;

protected:
    Camera* camera = new Camera();
    Cube cube;
};