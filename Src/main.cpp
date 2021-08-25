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

    void CheckInput();
    void UpdateState(unsigned int td_milli);
    void RenderFrame();
    void RenderOSD();
};

bool AssignmentApp::Tick(unsigned int td_milli)
{
    m_QuitApp = false;
    CheckInput();
    UpdateState(td_milli);
    RenderFrame();
    return m_QuitApp;
}

void AssignmentApp::CheckInput()
{
    const Uint8* keys;
    SDL_PumpEvents();
    if (keys = SDL_GetKeyboardState(nullptr)) {
        if (keys[SDL_SCANCODE_ESCAPE]) {
            m_QuitApp = true;
        }
    }
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

    gltBeginDraw();
     gltColor(0.0f, 1.0f, 0.0f, 1.0f);
     gltDrawText2D(hello_msg, 10, 10, 2.0);
    gltEndDraw();

    gltDeleteText(hello_msg);
}

void AssignmentApp::RenderFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderOSD();

    // The rest of your frame rendering code goes here
    scene->draw();

    SDL_GL_SwapWindow(m_SDLWindow);
}

int AssignmentApp::Init()
{
    if (int err = RTRApp::Init() != 0) {
        return err;
    }
    gltInit();
    glViewport(0, 0, m_WindowWidth, m_WindowHeight);
    scene->init();

    return 0;
}

void AssignmentApp::Done()
{
    gltTerminate();
    scene->done();

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
