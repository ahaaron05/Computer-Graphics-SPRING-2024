#version 330 core

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;
out vec4 fragColor;

uniform vec3 lightPos;
uniform vec3 objColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * objColor;
	fragColor = vec4(result, 1.0f);
}