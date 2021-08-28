#include "SceneOne.h"

void SceneOne::init(float width, float height)
{
    name = 1;
    camera->init(width, height);
    cube->init();

    glEnable(GL_LIGHTING);

    this->setup_lighting();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void SceneOne::draw()
{
    camera->updateProjection();
    camera->updateView();

    update_forward(camera, lights.at(0));

    cube->draw();
}

void SceneOne::done()
{
    cube->done();
    lights.clear();
    position.clear();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void SceneOne::setup_lighting()
{
    int j = 0;
    for (int i = 16384; i < 16392; i++)
    {
        Lighting light;
        lights.push_back(light);
        lights.at(j).light_num = i;
        j++;
    }

    lights.at(0).light_diffuse = { 1.0, 1.0, 1.0, 1.0 };
    lights.at(1).light_diffuse = { 0.0, 0.0, 0.0, 1.0 };
    lights.at(2).light_diffuse = { 1.0, 1.0, 1.0, 1.0 };
    lights.at(3).light_diffuse = { 1.0, 0.0, 0.0, 1.0 };
    lights.at(4).light_diffuse = { 0.0, 1.0, 0.0, 1.0 };
    lights.at(5).light_diffuse = { 0.0, 0.0, 1.0, 1.0 };
    lights.at(6).light_diffuse = { 1.0, 0.0, 1.0, 1.0 };
    lights.at(7).light_diffuse = { 0.0, 0.1, 1.0, 1.0 };

    lights.at(0).light_position = { 20.0, 0.0, 0.0, 1.0 };
    lights.at(1).light_position = { -20.0, 0.0, 0.0, 1.0 };
    lights.at(2).light_position = { 0.0, 20.0, 0.0, 1.0 };
    lights.at(3).light_position = { 0.0, -20.0, 0.0, 1.0 };
    lights.at(4).light_position = { 0.0, 0.0, 20.0, 1.0 };
    lights.at(5).light_position = { 0.0, 0.0, -20.0, 1.0 };
    lights.at(6).light_position = { 20.0, 20.0, 0.0, 1.0 };
    lights.at(7).light_position = { -20.0, 20.0, 0.0, 1.0 };
    
    for (int i = 0; i < 8; i++)
    {
        if (i == 0) 
        {
            set_global_light(camera, lights.at(i));
        }
        else 
        {
            set_positional_light(lights.at(i));
        }
    }
}

void SceneOne::turn_off(int light_num)
{
    glDisable(light_num);
}

void SceneOne::turn_on(int light_num)
{
    glEnable(light_num);
}

void SceneOne::set_global_light(Camera* camera, Lighting light)
{
    glLightfv(light.light_num, GL_AMBIENT, glm::value_ptr(light.light_ambient));
    glLightfv(light.light_num, GL_DIFFUSE, glm::value_ptr(light.light_diffuse));
    glLightfv(light.light_num, GL_SPECULAR, glm::value_ptr(light.light_specular));
    glLightfv(light.light_num, GL_POSITION, glm::value_ptr(glm::vec4(camera->front * glm::vec3(-1.0), 0.0f)));
    glEnable(light.light_num);
}

void SceneOne::set_positional_light(Lighting light)
{
    glLightfv(light.light_num, GL_AMBIENT, glm::value_ptr(light.light_ambient));
    glLightfv(light.light_num, GL_DIFFUSE, glm::value_ptr(light.light_diffuse));
    glLightfv(light.light_num, GL_SPECULAR, glm::value_ptr(light.light_specular));
    glLightfv(light.light_num, GL_POSITION, glm::value_ptr(light.light_position));
    glLightf(light.light_num, GL_CONSTANT_ATTENUATION, light.const_attenuation);
    glLightf(light.light_num, GL_LINEAR_ATTENUATION, light.linear_attenuation);
    glLightf(light.light_num, GL_QUADRATIC_ATTENUATION, light.quadratic_attenuation);
    glEnable(light.light_num);
}

void SceneOne::update_forward(Camera* camera, Lighting light)
{
    glLightfv(light.light_num, GL_POSITION, glm::value_ptr(glm::vec4(camera->front * glm::vec3(-1.0), 0.0f)));
}


