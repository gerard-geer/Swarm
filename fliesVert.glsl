#version 400

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

smooth out vec3 theColor;

void main()
{
	gl_Position = vec4(inPosition.x*2-1, inPosition.y*-2+1, 1.0, 1);
	theColor = inColor;
}