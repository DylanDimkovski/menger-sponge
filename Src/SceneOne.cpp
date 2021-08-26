#include "SceneOne.h"

void SceneOne::init(float width, float height)
{
    camera->init(width, height);
    cube->init();
    lighting->init(camera);

    depthtest = true;
    backface = true;
    name = "1";
}

void SceneOne::draw()
{
    lighting->update_forward(camera);
    (depthtest) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    (backface) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

    if (backface) 
    {
        glCullFace(GL_BACK);
    }

    camera->updateProjection();
    camera->updateView();

    cube->draw();
}

void SceneOne::done()
{
    camera->done();
    cube->done();
}

