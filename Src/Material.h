#pragma once
#include <glad/glad.h>
#include <glm/ext.hpp>
class Material 
{
public:
	void apply_material();

	glm::vec4 mat_ambient;
	glm::vec4 mat_diffuse;
	glm::vec4 mat_specular;
	GLfloat shine;
};