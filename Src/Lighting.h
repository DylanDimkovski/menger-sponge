#pragma once
#include "Camera.h"
#include <glad/glad.h>
class Lighting 
{
public:
	void init(Camera* camera);
	void draw();
	void done();
	void update_forward(Camera* camera);
protected:

};