#pragma once
#include "Scene.h"
#include <glm/ext.hpp>

class SceneOne : public Scene
{
public:
    void init();
    void draw();
    void done();

protected:
    Camera camera;
    Cube cube;
};

