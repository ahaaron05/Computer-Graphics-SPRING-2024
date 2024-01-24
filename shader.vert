#version 330 core

layout (location = 0) in vec3 aPos; // attribute position
layout (location = 1) in vec3 aColor; // attribute color
layout (location = 2) in vec2 aTexCoord; // attribute texture coordinate

uniform float xOffset;

out vec3 color; // output a color to the fragment shader
out vec2 textureCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	color = aColor; // Set ourColor to the color data from vertices array
	textureCoord = vec2(aTexCoord.x, aTexCoord.y);
}