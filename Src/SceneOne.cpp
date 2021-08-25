#include "Scene.h"
#include <glad/glad.h>
#include <glm/ext.hpp>

class SceneOne : public Scene 
{
public:
    void init()
    {
        GLfloat depth = 1.0f;
        cube.init(depth, 10.0f);

        camera->init();

        glm::mat4 projection = glm::perspective(glm::radians(80.0f), 2056.0f / 1080.0f, 0.1f, 100.0f);

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    void draw()
    {
        camera->updateView();

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(camera->view));

        cube.draw();
    }

    void done()
    {
        camera->done();
        cube.done();
        delete camera;
    }
};

