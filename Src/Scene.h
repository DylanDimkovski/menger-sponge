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
#include "Lighting.h"
#include "Material.h"
#include <glm/ext.hpp>
#include <glad/glad.h>
#include <iostream>

class Scene
{
public:

    Scene() 
    {
        camera = new Camera();
        cube = new Cube(1, 5);
        lighting = new Lighting();
        material = new Material();
    }

    ~Scene()
    {
        delete camera;
        delete cube;
    }

    Camera* camera;
    Cube* cube;
    Lighting* lighting;
    Material* material;

    virtual void init(float width, float height) {};
    virtual void draw() {};
    virtual void done() {};

    bool depthtest;
    bool backface;

    std::string name;
};