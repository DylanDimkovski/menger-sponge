#include "Lighting.h"

void Lighting::init(Camera* camera)
{
	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { camera->front.x + camera->position.x, camera->front.y + camera->position.y, camera->front.z + camera->position.z, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Lighting::draw()
{

}

void Lighting::done()
{

}

void Lighting::update_forward(Camera* camera)
{
	GLfloat light_position[] = { camera->front.x + camera->position.x, camera->front.y + camera->position.y, camera->front.z + camera->position.z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
