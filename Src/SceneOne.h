#pragma once
#include "Scene.h"
#include "Lighting.h"
#include <glm/ext.hpp>

class SceneOne : public Scene
{
public:
    void init(float width, float height);
    void draw();
    void done();
    void setup_lighting();


    void turn_off(int light_num);
    void turn_on(int light_num);
    void set_global_light(Camera* camera, Lighting light);
    void set_positional_light(Lighting light);
    void update_forward(Camera* camera, Lighting light);
};

