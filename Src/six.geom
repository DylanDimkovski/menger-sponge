#version 400
layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float animation;

vec3 p1 = vec3(gl_in[0].gl_Position);
vec3 p2 = vec3(gl_in[1].gl_Position);
vec3 p3 = vec3(gl_in[2].gl_Position);

out GS_OUT{
    vec3 position;
    vec3 normal;
}gs_out;

#define PI 3.1415926538

float atan2(in float y, in float x)
{
    bool s = (abs(x) > abs(y));
    return mix(PI/2.0 - atan(x,y), atan(y,x), s);
}

vec3 lerp(vec3 begin, vec3 end, float animation)
{
	return (begin + (end - begin) * (animation * animation));
}

vec3 calculate_morph(vec3 begin)
{
	float d = length(begin);
	float r = max(max(abs(begin.x), abs(begin.y)), abs(begin.z));

	float theta = acos(begin.z / d);
	float phi = atan2(begin.y, begin.x);

	float fx = r * sin(theta) * cos(phi);
	float fy = r * sin(theta) * sin(phi);
	float fz = r * cos(theta);

	return vec3(fx, fy, fz);
}

void main()
{
    for(int i = 0; i < gl_in.length(); i++)
    {
        vec3 my_position = vec3(gl_in[i].gl_Position);
        gl_Position = projection * view * model * vec4(lerp(my_position, calculate_morph(my_position), (animation*animation)), 1.0f);
        vec3 v1 = p1 - p3;
        vec3 v2 = p2 - p3;

        gs_out.normal = normalize(cross(v1, v2));
        gs_out.position = vec3(gl_Position);

        EmitVertex();
    }
    EndPrimitive();
}