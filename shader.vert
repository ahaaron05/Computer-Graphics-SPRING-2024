#version 330 core

layout (location = 0) in vec3 aPos; // attribute position
layout (location = 1) in vec2 aTexCoord; // attribute texture coordinate
layout (location = 2) in vec3 aColor; // attribute color

out vec3 color; // output a color to the fragment shader
out vec2 textureCoord;

uniform mat4 model, view, projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	color = aColor; // Set ourColor to the color data from vertices array
	textureCoord = vec2(aTexCoord.x, aTexCoord.y);
}