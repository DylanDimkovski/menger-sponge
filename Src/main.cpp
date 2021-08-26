//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "RTRApp.h"

#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>

#include "SceneOne.h"

class AssignmentApp : public RTRApp
{
public:
    AssignmentApp(const char* title, bool fullscreen = false, int width = 1024, int height = 768)
        : RTRApp(title, fullscreen, width, height) {}
    int Init();
    void Done();
    bool Tick(unsigned int td_milli);

private:
    bool m_QuitApp = false;
    Scene* scene = new SceneOne();

    void CheckInput(unsigned int td_milli);
    void UpdateState(unsigned int td_milli);
    void RenderFrame();
    void RenderOSD();
};

bool AssignmentApp::Tick(unsigned int td_milli)
{
    m_QuitApp = false;
    CheckInput(td_milli);
    UpdateState(td_milli);
    RenderFrame();
    return m_QuitApp;
}

void AssignmentApp::CheckInput(unsigned int td_milli)
{
    SDL_Event e;
    const Uint8* keys;
    float speed = 10.0f * td_milli / 1000.0f;

    SDL_PumpEvents();
    if (keys = SDL_GetKeyboardState(nullptr)) {
        if (keys[SDL_SCANCODE_ESCAPE]) {
            m_QuitApp = true;
        }
        if (keys[SDL_SCANCODE_W]) {
            scene->camera->position += speed * scene->camera->front;
        }
        if (keys[SDL_SCANCODE_S]) {
            scene->camera->position -= speed * scene->camera->front;
        }
        if (keys[SDL_SCANCODE_Q]) {
            scene->camera->position -= speed * scene->camera->up;
        }
        if (keys[SDL_SCANCODE_E]) {
            scene->camera->position += speed * scene->camera->up;
        }
        if (keys[SDL_SCANCODE_A]) {
            scene->camera->position -= glm::normalize(glm::cross(scene->camera->front, scene->camera->up)) * speed;
        }
        if (keys[SDL_SCANCODE_D]) {
            scene->camera->position += glm::normalize(glm::cross(scene->camera->front, scene->camera->up)) * speed;
        }
    }

    if (SDL_PollEvent(&e) == 1)
    {
        auto sym = e.key.keysym.sym;

        if (e.type == SDL_KEYDOWN)
        {
            // Toggle Settings
            if (sym == SDLK_MINUS) {
                if (scene->cube->depth > 0)
                {
                    scene->cube->depth--;
                    scene->cube->done();
                    scene->cube->init();
                }
            }
            if (sym == SDLK_EQUALS) {
                if (scene->cube->depth < 5)
                {
                    scene->cube->depth++;
                    scene->cube->done();
                    scene->cube->init();
                }
            }
        }
    }

    scene->camera->mouseMove();
}

void AssignmentApp::UpdateState(unsigned int td_milli)
{
    // This is where we will do all our model updating, physics, etc...
}

// Render On-Screen Display
void AssignmentApp::RenderOSD()
{
    GLTtext* hello_msg = gltCreateText();
    gltSetText(hello_msg, "How bout now");

    GLTtext* test = gltCreateText();
    gltSetText(test, "Does this work");

    gltBeginDraw();
     gltColor(0.0f, 1.0f, 0.0f, 1.0f);
     gltDrawText2D(hello_msg, 10, 10, 2.0);
     gltDrawText2D(test, 10, 55, 2.0);
    gltEndDraw();

    gltDeleteText(hello_msg);
    gltDeleteText(test);

    glUseProgram(0);
}

void AssignmentApp::RenderFrame()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw();

    RenderOSD();

    SDL_GL_SwapWindow(m_SDLWindow);
}

int AssignmentApp::Init()
{
    if (int err = RTRApp::Init() != 0) {
        return err;
    }

    gltInit();
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);

    scene->init((float) m_WindowWidth, (float) m_WindowHeight);

    return 0;
}

void AssignmentApp::Done()
{
    scene->done();
    gltTerminate();
    RTRApp::Done();
}


static const char* MAIN_WINDOW_TITLE = "COSC1226 - Assignment 1";

int main(int argc, char** argv)
{
    AssignmentApp* app = new AssignmentApp(MAIN_WINDOW_TITLE, false);
    if (int err = app->Init() != 0) {
        std::cout << "RTR:ERROR: Failed to initialise application. Please see error messages for details..." << std::endl;
        return -1;
    };
    app->Run();
    app->Done();
    return 0;
}
