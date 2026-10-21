#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec4 tint = vec4(1.0);

void main()
{
	FragColor = texture(ourTexture, TexCoord) * tint;
}