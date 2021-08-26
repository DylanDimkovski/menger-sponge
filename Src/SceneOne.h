#pragma once
#include "Scene.h"
#include <glm/ext.hpp>

class SceneOne : public Scene
{
public:
    void init(float width, float height);
    void draw();
    void done();
};

