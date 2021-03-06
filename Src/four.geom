#version 400 core
layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform mat4 projection;
uniform mat4 view;

in Vertex{
	mat4 Model;
}vertex_in[];

vec3 p1 = vec3(gl_in[0].gl_Position);
vec3 p2 = vec3(gl_in[1].gl_Position);
vec3 p3 = vec3(gl_in[2].gl_Position);

out GS_OUT{
    vec3 position;
    vec3 normal;
}gs_out;

void main()
{
    for(int i = 0; i < 3; i++)
    {
        gl_Position = projection * view * vertex_in[i].Model * gl_in[i].gl_Position;
        vec3 v1 = p1 - p3;
        vec3 v2 = p2 - p3;

        gs_out.normal = normalize(cross(v1, v2));
        gs_out.position = vec3(gl_Position);

        EmitVertex();
    }
    EndPrimitive();
}