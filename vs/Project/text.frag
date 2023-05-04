#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;
uniform vec3 ourColor;

void main()
{
		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(ourTexture, TexCoords).r);
		color = vec4(ourColor, 1.0) * sampled;
	
}