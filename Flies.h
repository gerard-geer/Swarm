#pragma once
#include <stdlib.h>
#include <vector>
#include "Fly.h"
#include "Shaders.h"
//#include "GL\glut.h"
class Flies
{
public:
	Flies(int amount);
	void initFlies(char * vert, char * frag, char * name);
	void gravitate(float x, float y);
	~Flies(void);
	void renderFrame(void);
private:
	void loadShader(void);
	float * createVertLocDataArray(void);
	float * createVertColorDataArray(void);
	std::vector<Fly> flies;
	GLuint vboHandles[2];
	GLuint vertexArray;

	ShaderProgram shader;
	Shader vertex;
	Shader fragment;
};

