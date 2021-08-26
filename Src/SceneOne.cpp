#include "SceneOne.h"

void SceneOne::init(float width, float height)
{
    camera->init(width, height);

    cube->init();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void SceneOne::draw()
{
    camera->updateProjection();
    camera->updateView();

    cube->draw();
}

void SceneOne::done()
{
    camera->done();
    cube->done();
}

