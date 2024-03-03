#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
	//! AMBIENT
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	//! DIFFUSE
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	//! SPECULAR
	float specularStrength = 0.5f;
	float shininess = 256;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflecDir = reflect(-lightDir, norm);
	float specular = pow(max(dot(viewDir, reflecDir), 0.0), shininess);
	vec3 result = (ambient + diffuse + specular) * objColor;
	//! PHONG
	fragColor = vec4(result, 1.0f);
}