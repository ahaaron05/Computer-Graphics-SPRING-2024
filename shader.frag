#version 330 core

out vec4 fragColor;

in vec3 position;
in vec3 color;
in vec2 textureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    fragColor = mix(texture(texture1, textureCoord) * vec4(color, 1.0), texture(texture2, textureCoord) * vec4(color, 1.0), 0.32);
}