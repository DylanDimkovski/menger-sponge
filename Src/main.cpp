//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "RTRApp.h"
#include "SceneOne.h"

#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>


class AssignmentApp : public RTRApp
{
public:
    AssignmentApp(const char* title, bool fullscreen = false, int width = 2560, int height = 1440)
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
            if (sym == SDLK_z) {
                scene->depthtest = !scene->depthtest;
            }
            if (sym == SDLK_c) {
                scene->backface = !scene->backface;
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
    GLTtext* text = gltCreateText();
    gltBeginDraw();
    gltColor(0.0f, 1.0f, 0.0f, 1.0f);

    gltSetText(text, ("Scene: " + scene->name).c_str());
    gltDrawText2D(text, 10, 0, 2.0);

    gltSetText(text, ("Display: " + std::to_string((float)m_WindowWidth) + 'x' + std::to_string(m_WindowHeight)).c_str());
    gltDrawText2D(text, 10, 50, 1.8);

    gltSetText(text, "FPS: 0");
    gltDrawText2D(text, 10, 100, 2.0);

    gltSetText(text, ("Subdivisions: " + std::to_string((int)scene->cube->depth)).c_str());
    gltDrawText2D(text, 10, 150, 2.0);

    gltSetText(text, ("Vertices: " + std::to_string(scene->cube->vertex.size())).c_str());
    gltDrawText2D(text, 10, 200, 2.0);

    gltSetText(text, ("Faces:" + std::to_string(pow(20,scene->cube->depth) * 6)).c_str());
    gltDrawText2D(text, 10, 250, 2.0);

    gltSetText(text, "Data:");
    gltDrawText2D(text, 10, 300, 2.0);

    gltSetText(text, "Lighting:");
    gltDrawText2D(text, 10, 350, 2.0);

    (scene->depthtest) ? gltSetText(text, "Depth Testing: On") : gltSetText(text, "Depth Testing: Off");
    gltDrawText2D(text, 10, 400, 2.0);

    (scene->backface) ? gltSetText(text, "Backface Culling: On") : gltSetText(text, "Backface Culling: Off");
    gltDrawText2D(text, 10, 450, 2.0);

    gltEndDraw();
    gltDeleteText(text);

    glUseProgram(0);
}

void AssignmentApp::RenderFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
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

    gltInit();
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
