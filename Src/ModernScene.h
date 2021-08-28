#pragma once
#include "Scene.h"
#include "Shader.h"

class ModernScene : public Scene
{
public:
    virtual void init(float width, float height) {};
    virtual void draw() {};
    virtual void done() {};
    virtual void setup_lighting();
    virtual void setup_vertex() {};
protected:
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int EBO = 0;

    Shader* shader = new Shader();
};

