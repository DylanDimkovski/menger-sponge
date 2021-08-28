#include "Cube.h"

Cube::Cube(float depth, float size)
{
	this->count = 0;
	this->depth = depth;
	this->size = size;

	ruby.mat_ambient = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
	ruby.mat_diffuse = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
	ruby.mat_specular = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
	ruby.shine = { 76.8f };

	emerald.mat_ambient = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	emerald.mat_diffuse = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
	emerald.mat_specular = { 0.633f, 0.727811f, 0.633f, 0.55f };
	emerald.shine = { 76.8f };

	turquoise.mat_ambient = { 0.1f, 0.18725f, 0.1745f, 0.8f };
	turquoise.mat_diffuse = { 0.396f, 0.2f, 0.85f, 0.8f };
	turquoise.mat_specular = { 0.297254f, 0.30829f, 0.306678f, 0.8f };
	turquoise.shine = { 12.8f };
}

void Cube::init()
{
	generate_sponge(depth, size, glm::vec3(0.0f, 0.0f, 0.0f));
}

void Cube::draw()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < index.size(); i += 3)
	{
		glm::vec3 p1 = vertex.at(index.at(i));
		glm::vec3 p2 = vertex.at(index.at(i + 1));
		glm::vec3 p3 = vertex.at(index.at(i + 2));

		glm::vec3 v1 = p1 - p3;
		glm::vec3 v2 = p2 - p3;

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
		glNormal3fv(glm::value_ptr(normal));
		
		selectColor(normal);

		glVertex3fv(glm::value_ptr(p1));
		glVertex3fv(glm::value_ptr(p2));
		glVertex3fv(glm::value_ptr(p3));
	}

	glEnd();
	glPopMatrix();
}

void Cube::done()
{
	vertex.clear();
	index.clear();
	count = 0.0f;
}

void Cube::selectColor(glm::vec3 normal)
{
	if (normal.x != 0)
	{
		//Red
		glColor3f(1.0f, 0.0f, 0.0f);
		ruby.apply_material();
	}
	else if (normal.y != 0)
	{
		//Green
		glColor3f(0.0f, 1.0f, 0.0f);
		emerald.apply_material();
	}
	else if (normal.z != 0)
	{
		//Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		turquoise.apply_material();
	}
}

void Cube::generate_sponge(GLfloat d, GLfloat e, glm::vec3 parent)
{
	if (d == 0 && vertex.empty())
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

					if (d == 1)
					{
						generate_cube(subSize, parent, child);
					}
					else
					{
						generate_sponge(d - 1, subSize, child);
					}
				}
			}
		}
	}
}

void Cube::generate_cube(GLfloat e, glm::vec3 parent, glm::vec3 child)
{
	GLfloat new_vertex = e / 2.0f;
	int current = count * 8.0f;
	
	vertex.insert(vertex.end(), {
		child + glm::vec3(new_vertex, new_vertex, new_vertex),
		child + glm::vec3(-new_vertex, new_vertex, new_vertex),
		child + glm::vec3(-new_vertex, -new_vertex, new_vertex),
		child + glm::vec3(new_vertex, -new_vertex, new_vertex),

		child + glm::vec3(new_vertex, new_vertex, -new_vertex),
		child + glm::vec3(-new_vertex, new_vertex, -new_vertex),
		child + glm::vec3(-new_vertex, -new_vertex, -new_vertex),
		child + glm::vec3(new_vertex, -new_vertex, -new_vertex),
	});

	//Front Face
	index.insert(index.end(), {
		current + 1,
		current + 2,
		current + 3,
		current + 3,
		current + 0,
		current + 1,
	});

	//Back Face
	index.insert(index.end(), {
		current + 5,
		current + 4,
		current + 7,
		current + 7,
		current + 6,
		current + 5,
	});

	//Left Face
	index.insert(index.end(), {
		current + 1,
		current + 5,
		current + 6,
		current + 6,
		current + 2,
		current + 1,
	});

	//Right Face
	index.insert(index.end(), {
		current + 0,
		current + 3,
		current + 7,
		current + 7,
		current + 4,
		current + 0,
	});

	//Top Face
	index.insert(index.end(), {
		current + 1,
		current + 0,
		current + 4,
		current + 4,
		current + 5,
		current + 1,
	});

	//Bottom Face
	index.insert(index.end(), {
		current + 3,
		current + 2,
		current + 6,
		current + 6,
		current + 7,
		current + 3,
	});

	count++;
}

