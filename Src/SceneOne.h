#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/ext.hpp>

class SceneOne : public Scene
{
public:
    void init();
    void draw();
    void done();
};

