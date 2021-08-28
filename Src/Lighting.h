#pragma once
#include "Camera.h"
#include <glad/glad.h>
class Lighting 
{
public:
	Lighting();

	glm::vec4 light_ambient;
	glm::vec4 light_diffuse;
	glm::vec4 light_specular;
	glm::vec4 light_position;

	GLfloat const_attenuation;
	GLfloat linear_attenuation;
	GLfloat quadratic_attenuation;

	int light_num;
};