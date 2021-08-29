//-----------------------------------------------------------------------------
// main.cpp
//-----------------------------------------------------------------------------
// Assignment 1 Starter Code
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#include "RTRApp.h"
#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"
#include "SceneFour.h"
#include "SceneFive.h"
#include "SceneSix.h"

#include "Chrono.h"

#define GLT_IMPLEMENTATION
#include <gltext/gltext.h>


class AssignmentApp : public RTRApp
{
public:
    AssignmentApp(const char* title, bool fullscreen = true, int width = 2560, int height = 1440)
        : RTRApp(title, fullscreen, width, height) {}
    int Init();
    void Done();
    bool Tick(unsigned int td_milli);

private:
    bool m_QuitApp = false;
    bool full_mode = true;
    Scene* scene = new SceneOne();
    std::vector<std::string> text_to_draw;
    Chrono* chrono = new Chrono();

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
                    scene->setup_vertex();
                }
            }
            if (sym == SDLK_EQUALS) {
                if (scene->cube->depth < 5)
                {
                    scene->cube->depth++;
                    scene->cube->done();
                    scene->cube->init();
                    scene->setup_vertex();
                }
            }

            if (sym == SDLK_COMMA) {
                if (scene->num_of_lights > 1)
                {
                    scene->num_of_lights--;
                    static_cast<SceneOne*>(scene)->turn_off(scene->lights.at(scene->num_of_lights).light_num);
                }
            }
            if (sym == SDLK_PERIOD) {
                if (scene->num_of_lights < 7)
                {
                    scene->num_of_lights++;
                    static_cast<SceneOne*>(scene)->turn_on(scene->lights.at(scene->num_of_lights).light_num);
                }
            }

            if (sym == SDLK_l) {
                scene->lighting = !scene->lighting;
                (scene->lighting) ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
            }

            if (sym == SDLK_h) {
                full_mode = !full_mode;
            }

            if (sym == SDLK_z) {
                scene->depthtest = !scene->depthtest;
                (scene->depthtest) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
            }
            if (sym == SDLK_c) {
                scene->backface = !scene->backface;
                (scene->backface) ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

                if (scene->backface)
                {
                    glCullFace(GL_BACK);
                }
            }

            if (sym == SDLK_1) {
                scene->done();
                delete scene;
                scene = new SceneOne();
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }

            if (sym == SDLK_2) {
                scene->done();
                delete scene;
                scene = new SceneTwo();
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }

            if (sym == SDLK_3) {
                scene->done();
                delete scene;
                scene = new SceneThree();
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }

            if (sym == SDLK_4) {
                scene->done();
                delete scene;
                scene = new SceneFour();
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }

            if (sym == SDLK_5) {
                scene->done();
                delete scene;
                scene = new SceneFive(chrono);
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }

            if (sym == SDLK_6) {
                scene->done();
                delete scene;
                scene = new SceneSix(chrono);
                scene->init((float)m_WindowWidth, (float)m_WindowHeight);
            }
        }
    }

    scene->camera->mouseMove();
}

void AssignmentApp::UpdateState(unsigned int td_milli)
{
}

// Render On-Screen Display
void AssignmentApp::RenderOSD()
{
    if (full_mode) 
    {
        text_to_draw.push_back("Scene: " + std::to_string(scene->name));
        text_to_draw.push_back("Display: " + std::to_string(m_WindowWidth) + 'x' + std::to_string(m_WindowHeight));
        text_to_draw.push_back("FPS: " + std::to_string((int)(chrono->fps)));
        text_to_draw.push_back("Subdivisions: " + std::to_string((int)scene->cube->depth));
        if (scene->name == 3 || scene->name == 4)
        {
            text_to_draw.push_back("Vertices: " + std::to_string(scene->cube->vertex.size() * 9));
            text_to_draw.push_back("Faces:" + std::to_string(((int)pow(20, scene->cube->depth) * 6) * 9));
            text_to_draw.push_back("Data: " + std::to_string(scene->cube->vertex.size() * sizeof(glm::vec3) * 9) + " bytes");
        }
        text_to_draw.push_back("Vertices: " + std::to_string(scene->cube->vertex.size()));
        text_to_draw.push_back("Faces:" + std::to_string((int)pow(20, scene->cube->depth) * 6));
        text_to_draw.push_back("Data: " + std::to_string(scene->cube->vertex.size() * sizeof(glm::vec3)) + " bytes");
        text_to_draw.push_back((scene->lighting) ? "Lighting: On" : "Lighting: Off");
        text_to_draw.push_back((scene->depthtest) ? "Depth Testing: On" : "Depth Testing: Off");
        text_to_draw.push_back((scene->backface) ? "Backface Culling: On" : "Backface Culling: Off");

        for (int i = 0; i < 10; i++)
        {
            GLTtext* text = gltCreateText();
            gltBeginDraw();
            gltColor(0.0f, 1.0f, 0.0f, 1.0f);
            gltSetText(text, text_to_draw.at(i).c_str());
            gltDrawText2D(text, 10, (50 * i), 2.0);
            gltEndDraw();
            gltDeleteText(text);
        }

        text_to_draw.clear();
        glUseProgram(0);
    }
    else 
    {
        GLTtext* text = gltCreateText();
        gltBeginDraw();
        gltColor(0.0f, 1.0f, 0.0f, 1.0f);
        gltSetText(text, ("FPS: " + std::to_string((int)(chrono->fps))).c_str());
        gltDrawText2D(text, 10, 0, 2.0);
        gltEndDraw();
        gltDeleteText(text);
        glUseProgram(0);
    }
}

void AssignmentApp::RenderFrame()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw();
    RenderOSD();

    chrono->calculate_delta();

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
    AssignmentApp* app = new AssignmentApp(MAIN_WINDOW_TITLE, true);
    if (int err = app->Init() != 0) {
        std::cout << "RTR:ERROR: Failed to initialise application. Please see error messages for details..." << std::endl;
        return -1;
    };
    app->Run();
    app->Done();
    return 0;
}
