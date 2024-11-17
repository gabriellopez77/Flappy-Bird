#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform vec3 color;
uniform bool isColored;

void main()
{
	if (texture(myTexture, TexCoord).a < 0.1)
		discard;

	FragColor = texture(myTexture, TexCoord);
}