#pragma once
#include "ModernScene.h"
#include "Chrono.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SceneFive : public ModernScene
{
public:
    SceneFive(Chrono* c) : chrono(c) {};
    void init(float width, float height);
    void draw();
    void done();
    void setup_vertex();
    glm::vec3 lerp(glm::vec3 begin, glm::vec3 end, float animation);
    glm::vec3 calculate_morph(glm::vec3 begin);
    void update_morphed();
    void update_animation();

    float direction = 1.0f;
    float animation = 1.0f;
    std::vector<glm::vec3> morphed;
    Chrono* chrono;
};
