#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform vec3 color;
uniform bool isColored;
uniform float alpha;

vec4 tex = texture(myTexture, TexCoord);

void main()
{
	if (tex.a < 0.1f)
		discard;

	tex.a = alpha;
	FragColor = tex;
}