#include "Cube.h"
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <math.h>

#include <iostream>
void Cube::init(GLfloat depth, GLfloat e)
{
	count = 0.0f;
	generate_sponge(depth, e, glm::vec3(0.0f, 0.0f, 0.0f));
}

void Cube::draw()
{
	//std::cout << vertex.size() << ", " << index.size() << std::endl;

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);

	for (size_t i = 0; i < vertex.size(); i += 3)
	{
		glVertex3fv(glm::value_ptr(vertex.at(index.at(i))));
		glVertex3fv(glm::value_ptr(vertex.at(index.at(i + 1))));
		glVertex3fv(glm::value_ptr(vertex.at(index.at(i + 2))));
	}

	glEnd();
}

void::Cube::done()
{
	vertex.clear();
	index.clear();
	count = 0.0f;
}

void::Cube::generate_sponge(GLfloat depth, GLfloat e, glm::vec3 parent)
{
	if (depth == 0 && vertex.empty())
	{
		generate_cube(e, parent, glm::vec3(0, 0, 0));
		return;
	}

	for (float x = -1.0f; x <= 1; x++)
	{
		for (float y = -1.0f; y <= 1; y++)
		{
			for (float z = -1.0f; z <= 1; z++)
			{
				if (!(x == 0 && z == 0) && !(y == 0 && z == 0) && !(x == 0 && y == 0))
				{
					float subSize = 1.0f / 3.0f * e;
					glm::vec3 child = glm::vec3(x, y, z) * subSize + parent;

					if (depth == 1)
					{
						generate_cube(subSize, child, parent);
					}
					else
					{
						generate_sponge(depth - 1, subSize, child);
					}
				}
			}
		}
	}
}

void Cube::generate_cube(GLfloat e, glm::vec3 parent, glm::vec3 child)
{
	GLfloat new_vertex = e;

	int current = count * 8.0f;
	count++;

	glm::vec3 pos = child * e + parent;
	new_vertex /= 2.0f;

	vertex.insert(vertex.end(), {
		pos + glm::vec3(new_vertex, new_vertex, new_vertex), // north east top vertex
		pos + glm::vec3(new_vertex, -new_vertex, new_vertex), // south east top vertex
		pos + glm::vec3(-new_vertex, new_vertex, new_vertex), // north west top vertex
		pos + glm::vec3(-new_vertex, -new_vertex, new_vertex), // south west top vertex
		pos + glm::vec3(new_vertex, new_vertex, -new_vertex), // north east bottom vertex
		pos + glm::vec3(new_vertex, -new_vertex, -new_vertex), // south east bottom vertex
		pos + glm::vec3(-new_vertex, new_vertex, -new_vertex), // north west bottom vertex
		pos + glm::vec3(-new_vertex, -new_vertex, -new_vertex), // south west bottom vertex
		});

	//Front Face
	index.insert(index.end(), {
		current + 0,
		current + 1,
		current + 2,
		current + 0,
		current + 3,
		current + 2,
		});

	//Back Face
	index.insert(index.end(), {
		current + 5,
		current + 6,
		current + 7,
		current + 5,
		current + 4,
		current + 7,
		});

	//Left Face
	index.insert(index.end(), {
		current + 1,
		current + 6,
		current + 7,
		current + 1,
		current + 2,
		current + 7,
		});

	//Right Face
	index.insert(index.end(), {
		current + 5,
		current + 0,
		current + 3,
		current + 5,
		current + 4,
		current + 3,
		});

	//Top Face
	index.insert(index.end(), {
		current + 0,
		current + 5,
		current + 6,
		current + 0,
		current + 1,
		current + 6,
		});

	//Bottom Face
	index.insert(index.end(), {
		current + 3,
		current + 4,
		current + 7,
		current + 3,
		current + 2,
		current + 7,
		});
}

