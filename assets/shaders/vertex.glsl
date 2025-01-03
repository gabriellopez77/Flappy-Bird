#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 tex;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	TexCoord = tex.xy;
	gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);
}