#include "ModernScene.h"

void ModernScene::setup_lighting()
{
	for (int i = 0; i < 8; i++)
	{
		Lighting light;
		lights.push_back(light);
	}

	lights.at(0).light_diffuse = { 1.0, 1.0, 1.0, 1.0 };
	lights.at(1).light_diffuse = { 0.0, 0.0, 0.0, 1.0 };
	lights.at(2).light_diffuse = { 1.0, 1.0, 1.0, 1.0 };
	lights.at(3).light_diffuse = { 1.0, 0.0, 0.0, 1.0 };
	lights.at(4).light_diffuse = { 0.0, 1.0, 0.0, 1.0 };
	lights.at(5).light_diffuse = { 0.0, 0.0, 1.0, 1.0 };
	lights.at(6).light_diffuse = { 1.0, 0.0, 1.0, 1.0 };
	lights.at(7).light_diffuse = { 0.0, 0.1, 1.0, 1.0 };

	lights.at(1).light_position = { -20.0, 0.0, 0.0, 1.0 };
	lights.at(2).light_position = { 0.0, 20.0, 0.0, 1.0 };
	lights.at(3).light_position = { 0.0, -20.0, 0.0, 1.0 };
	lights.at(4).light_position = { 0.0, 0.0, 20.0, 1.0 };
	lights.at(5).light_position = { 0.0, 0.0, -20.0, 1.0 };
	lights.at(6).light_position = { 20.0, 20.0, 0.0, 1.0 };
	lights.at(7).light_position = { -20.0, 20.0, 0.0, 1.0 };
}
