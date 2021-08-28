#version 400 core
struct Material {
    vec3 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
}; 

struct Lighting{
    vec3 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
};

in FS_IN{
    vec3 position;
    vec3 normal;
}fs_in;

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
    vec4 ambient = directional.diffuse * material.diffuse;

    // diffuse;
    float diff = max(dot(fs_in.normal, cam_dir), 0.0);
    vec4 diffuse = directional.diffuse * diff * material.diffuse;

    // specular
    vec3 halfwayDir = -cam_dir;   
    float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0), material.shininess);
    vec4 specular = directional.specular * spec * material.specular;

    // Output
    FragColor += ambient + diffuse + specular;
}

void calculate_postional(Material material)
{
    for(int i = 1; i < lights.length(); i ++)
    {
        Lighting light = lights[i];

        // ambient
        vec4 ambient = light.diffuse * material.diffuse;
        vec3 light_dir = normalize(vec3(light.position) - fs_in.position);

        // diffuse;
        float diff = max(dot(fs_in.normal, light_dir), 0.0);
        vec4 diffuse = light.diffuse * diff * material.diffuse;

        // specular
        vec3 view_dir = normalize(cam_pos - fs_in.position);
        vec3 halfwayDir = normalize(light_dir + view_dir);   
        float spec = pow(max(dot(fs_in.normal, halfwayDir), 0.0), material.shininess);
        vec4 specular = light.specular * spec * material.specular;
        
        // Output
        FragColor += ambient + diffuse + specular;
    }
}

void main()
{
    Material material;
    if(fs_in.normal.x != 0)
    {
        material = red;
    }
    else if(fs_in.normal.y != 0)
    {
        material = green;
    }
    else if(fs_in.normal.z != 0)
    {
		material = blue;
    }
    calculate_directional(material);
    calculate_postional(material);
}
