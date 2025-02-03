#version 330 core

uniform vec4 hitBoxColor;

void main()
{
	gl_FragColor = hitBoxColor;
}