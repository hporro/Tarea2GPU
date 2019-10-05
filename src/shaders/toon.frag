#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 color;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
#define NUMBER_OF_POINT_LIGHTS 2
uniform PointLight lights[NUMBER_OF_POINT_LIGHTS];

uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

vec3 pointLightInfluence(PointLight light, vec3 norm){

    vec3 lightDir = normalize(light.position - FragPos);
    float intensity = dot(lightDir,norm);

    vec3 color;

    if (intensity > 0.95)
        color = light.color*material.diffuse*0.95;
    else if (intensity > 0.5)
        color = light.color*material.diffuse*0.5;
    else if (intensity > 0.15)
        color = light.color*material.diffuse*0.25;
    else
        color = light.color*material.diffuse*0.1;

    return color;
}

void main(){
    vec3 norm = normalize(Normal);

    vec3 result = vec3(0.0f);

    for(int i=0;i<NUMBER_OF_POINT_LIGHTS;i++){
        result += pointLightInfluence(lights[i],norm);
    }

    FragColor = vec4(result,1.0f);
}