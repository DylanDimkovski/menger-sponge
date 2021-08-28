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
#include <glm/ext.hpp>
#include <glad/glad.h>
#include <vector>

class Scene
{
public:

    Scene() 
    {
        camera = new Camera();
        cube = new Cube(1, 5);
        depthtest = true;
        backface = true;
        lighting = true;
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
    virtual void setup_lighting() {};
    virtual void setup_vertex() {};

    bool depthtest;
    bool backface;
    bool lighting;

    int num_of_lights = 8;

    int name;
    std::vector<Lighting> lights;
    std::vector<glm::vec4> position;
};