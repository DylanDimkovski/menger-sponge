#pragma once
#include "ModernScene.h"
class SceneFour : public ModernScene 
{
    void init(float width, float height);
    void draw();
    void done();
    void setup_vertex();
    void apply_translation();
    void apply_rotation();
};