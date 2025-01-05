#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D myTexture;
uniform float alpha;

uniform bool debugMode;
uniform vec4 hitBoxColor;

vec4 result;
void main()
{
	if (debugMode)
	{
		result = hitBoxColor;
		FragColor = result;
	}
	else
	{
		vec4 tex = texture(myTexture, TexCoord);
		if (tex.a < 0.1f)
			discard;

		tex.a = alpha;
		result = tex;
		FragColor = result;
	}

}