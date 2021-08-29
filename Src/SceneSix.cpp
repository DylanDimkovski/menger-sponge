#include "SceneSix.h"

void SceneSix::init(float width, float height)
{
	name = 6;
	camera->init(width, height);
	cube->init();
	setup_vertex();
	setup_lighting();
	shader->init("D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/basic.vert", "D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/basic.frag", "D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/six.geom");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void SceneSix::draw()
{
	shader->use();

	shader->setFloat("animation", animation);
	shader->setInt("num_of_lights", num_of_lights);
	shader->setBool("light_on", lighting);
	shader->setMat4("projection", camera->getProjection());
	shader->setMat4("model", glm::mat4(1.0));
	shader->setMat4("view", camera->getView());
	shader->setVec3("cam_pos", camera->position);
	shader->setVec3("cam_dir", camera->front);
	shader->setVec4("red.ambient", cube->ruby.mat_ambient);
	shader->setVec4("red.diffuse", cube->ruby.mat_diffuse);
	shader->setVec4("red.specular", cube->ruby.mat_specular);
	shader->setFloat("red.shininess", cube->ruby.shine);
	shader->setVec4("green.ambient", cube->emerald.mat_ambient);
	shader->setVec4("green.diffuse", cube->emerald.mat_diffuse);
	shader->setVec4("green.specular", cube->emerald.mat_specular);
	shader->setFloat("green.shininess", cube->emerald.shine);
	shader->setVec4("blue.ambient", cube->turquoise.mat_ambient);
	shader->setVec4("blue.diffuse", cube->turquoise.mat_diffuse);
	shader->setVec4("blue.specular", cube->turquoise.mat_specular);
	shader->setFloat("blue.shininess", cube->turquoise.shine);

	std::string index;
	for (int i = 0; i < num_of_lights; i++)
	{
		index = std::to_string(i);
		shader->setVec4("lights[" + index + "].ambient", lights.at(i).light_ambient);
		shader->setVec4("lights[" + index + "].diffuse", lights.at(i).light_diffuse);
		shader->setVec4("lights[" + index + "].specular", lights.at(i).light_specular);
		if (i == 0)
		{
			shader->setVec4("lights[" + index + "].position", glm::vec4(camera->front * glm::vec3(-1.0), 0.0f));
		}
		else { shader->setVec4("lights[" + index + "].position", lights.at(i).light_position); }
	}

	update_animation();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, cube->index.size(), GL_UNSIGNED_INT, 0);

	glUseProgram(0);
}

void SceneSix::done()
{
	cube->done();
	delete shader;
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void SceneSix::setup_vertex()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * cube->vertex.size(), &cube->vertex[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * cube->index.size(), &cube->index[0], GL_STATIC_DRAW);
}

void SceneSix::update_animation()
{
	if (animation >= 1.0f || animation <= 0.0f)
	{
		direction *= -1;
	}

	animation += chrono->elapsed * direction;
}