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
#include <glad/glad.h>

class Scene
{
public:

    Scene() 
    {
        camera = new Camera();
        cube = new Cube(1, 5);
    }

    ~Scene()
    {
        delete camera;
        delete cube;
    }

    Camera* camera;
    Cube* cube;

    virtual void init(float width, float height) {};
    virtual void draw() {};
    virtual void done() {};
};