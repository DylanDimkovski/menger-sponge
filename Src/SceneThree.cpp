#include "SceneThree.h"

void SceneThree::init(float width, float height)
{
	name = 3;
	camera->init(width, height);
	cube->init();
	setup_vertex();
	setup_lighting();
	shader->init("D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/basic.vert", "D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/basic.frag", "D:/Uni Work/RealTimeGraphics/A1_SURNAME_FIRSTNAME/menger-sponge/Src/basic.geom");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	for (int i = 0; i < 9; i++)
	{
		model.push_back(glm::mat4(1.0));
	}

	apply_translation();
}

void SceneThree::draw()
{
	apply_rotation();
	for (int i = 0; i < 9; i++)
	{
		camera->updateProjection();
		camera->updateView(model.at(i));

		shader->use();
		shader->setInt("num_of_lights", num_of_lights);
		shader->setBool("light_on", lighting);
		shader->setMat4("projection", camera->projection);
		shader->setMat4("model", glm::mat4(1.0));
		shader->setMat4("view", camera->view);
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
		for (int j = 0; j < num_of_lights; j++)
		{
			index = std::to_string(j);
			shader->setVec4("lights[" + index + "].ambient", lights.at(j).light_ambient);
			shader->setVec4("lights[" + index + "].diffuse", lights.at(j).light_diffuse);
			shader->setVec4("lights[" + index + "].specular", lights.at(j).light_specular);
			if (j == 0)
			{
				shader->setVec4("lights[" + index + "].position", glm::vec4(camera->front * glm::vec3(-1.0), 0.0f));
			}
			else { shader->setVec4("lights[" + index + "].position", lights.at(j).light_position); }
		}
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, cube->index.size(), GL_UNSIGNED_INT, 0);

		glUseProgram(0);
	}
}

void SceneThree::done()
{
	cube->done();
	model.clear();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void SceneThree::setup_vertex()
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

void SceneThree::apply_translation()
{
	model.at(0) = glm::translate(model.at(0), glm::vec3(-10.0, 10.0, -20.0));
	model.at(1) = glm::translate(model.at(1), glm::vec3(0.0, 10.0, -20.0));
	model.at(2) = glm::translate(model.at(2), glm::vec3(10.0, 10.0, -20.0));
	model.at(3) = glm::translate(model.at(3), glm::vec3(-10.0, 0.0, -20.0));
	model.at(4) = glm::translate(model.at(4), glm::vec3(0.0, 0.0, -20.0));
	model.at(5) = glm::translate(model.at(5), glm::vec3(10.0, 0.0, -20.0));
	model.at(6) = glm::translate(model.at(6), glm::vec3(-10.0, -10.0, -20.0));
	model.at(7) = glm::translate(model.at(7), glm::vec3(0.0, -10.0, -20.0));
	model.at(8) = glm::translate(model.at(8), glm::vec3(10.0, -10.0, -20.0));
}

void SceneThree::apply_rotation()
{
	model.at(0) = glm::rotate(model.at(0), glm::radians(0.1f), glm::vec3(1.0, 0.0, 0.0));
	model.at(1) = glm::rotate(model.at(1), glm::radians(0.1f), glm::vec3(0.0, 1.0, 0.0));
	model.at(2) = glm::rotate(model.at(2), glm::radians(0.1f), glm::vec3(0.0, 0.0, 1.0));
	model.at(3) = glm::rotate(model.at(3), glm::radians(0.1f), glm::vec3(1.0, 0.0, 1.0));
	model.at(4) = glm::rotate(model.at(4), glm::radians(0.1f), glm::vec3(1.0, 1.0, 0.0));
	model.at(5) = glm::rotate(model.at(5), glm::radians(0.1f), glm::vec3(0.5, 0.5, 0.5));
	model.at(6) = glm::rotate(model.at(6), glm::radians(0.1f), glm::vec3(0.7, 0.0, 0.2));
	model.at(7) = glm::rotate(model.at(7), glm::radians(0.1f), glm::vec3(0.0, 0.1, 1.0));
	model.at(8) = glm::rotate(model.at(8), glm::radians(0.1f), glm::vec3(0.5, 0.3, 0.8));
}
