#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in mat4 model;

out Vertex{
	mat4 Model;
}vertex;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertex.Model = model;
}