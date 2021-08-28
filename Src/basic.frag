#version 400 core
struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
}; 

struct Lighting{
    vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
};

in GS_OUT{
    vec3 position;
    vec3 normal;
}fs_in;

uniform bool light_on;
uniform int num_of_lights;
uniform Material red;
uniform Material green;
uniform Material blue;
uniform vec3 cam_pos;
uniform vec3 cam_dir;
uniform Lighting lights[8];

out vec4 FragColor;


void calculate_directional(Material material)
{
    Lighting directional = lights[0];

    // ambient
    vec4 ambient = directional.ambient * material.ambient;

    // diffuse;
    float diff = max(dot(fs_in.normal, -normalize(cam_dir)), 0.0);
    vec4 diffuse = directional.diffuse * (diff * material.diffuse);

    // specular
    vec3 halfwayDir = -normalize(cam_pos);   
    float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0), material.shininess);

    vec4 specular = directional.specular * (spec * material.specular);

    // Output
    FragColor += (ambient + diffuse + specular);
}

void calculate_postional(Material material)
{
    if(light_on)
    {
        for(int i = 1; i < num_of_lights; i++)
            {
            Lighting light = lights[i];

            // ambient
            vec4 ambient = light.ambient * material.ambient;
            vec3 light_dir = normalize(vec3(light.position) - fs_in.position);

            // diffuse;
            float diff = max(dot(fs_in.normal, light_dir), 0.0);
            vec4 diffuse = light.diffuse * (diff * material.diffuse);

            // specular
            vec3 view_dir = normalize(cam_pos - fs_in.position);
            vec3 halfwayDir = normalize(light_dir + view_dir);   
            float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0), material.shininess);
            vec4 specular = light.specular * (spec * material.specular);
            
            // Output
            FragColor += ambient + diffuse + specular;
        }
    }
}


void main()
{
    if(fs_in.normal.x != 0)
    {
        calculate_directional(red);
        calculate_postional(red);
    }
    else if(fs_in.normal.y != 0)
    {
        calculate_directional(green);
        calculate_postional(green);
    }
    else if(fs_in.normal.z != 0)
    {
        calculate_directional(blue);
        calculate_postional(blue);
    }
}
