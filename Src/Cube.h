#pragma once
//-----------------------------------------------------------------------------
// Cube.h
//-----------------------------------------------------------------------------
// Header Code For Cube
//-----------------------------------------------------------------------------
// RMIT University, COSC1226: Real-Time Rendering and 3D Game Programming
//-----------------------------------------------------------------------------
#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <math.h>

class Cube
{
public:
    void init(GLfloat depth, GLfloat e);
    void draw();
    void done();

    std::vector<glm::vec3> vertex;
    std::vector<int> index;
    float count;

protected:
    void generate_cube(GLfloat e, glm::vec3 parent, glm::vec3 child);
    void generate_sponge(GLfloat depth, GLfloat e, glm::vec3 pos);
};
