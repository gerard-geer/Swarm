#version 400

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inCoord;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(inPosition.x*2-1, inPosition.y*-2+1, 1.0, 1);
	texCoord = inCoord;
}