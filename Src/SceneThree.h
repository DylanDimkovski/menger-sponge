#pragma once
#include "ModernScene.h"
#include <sdl/SDL.h>
class SceneThree : public ModernScene
{
public:
    void init(float width, float height);
    void draw();
    void done();
    void setup_vertex();
    void apply_translation();
    void apply_rotation();
};
