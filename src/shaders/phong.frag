#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
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
    vec3 ambient = light.ambient * material.ambient;

    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main(){
    vec3 norm = normalize(Normal);

    vec3 result = vec3(0.0f);

    for(int i=0;i<NUMBER_OF_POINT_LIGHTS;i++){
        result+= pointLightInfluence(lights[i],norm);
    }

    FragColor = vec4(result, 1.0);
}