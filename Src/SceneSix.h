#pragma once
#include "ModernScene.h"
#include "Chrono.h"
class SceneSix : public ModernScene
{
public:
    SceneSix(Chrono* c) : chrono(c) {};
    void init(float width, float height);
    void draw();
    void done();
    void setup_vertex();
    void update_animation();

    float direction = 1.0f;
    float animation = 1.0f;
    Chrono* chrono;
};
