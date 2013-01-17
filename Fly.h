#pragma once
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glew.h>
#include <GL\glut.h>
#include <stdio.h>
class Fly
{
public:
	Fly(void);
	Fly(float x, float y, float velocity, float angle);
	~Fly(void);
	void handle(void);
	void render(void);
	void gravitate(float x, float y);
	float vertLocations[6];
	float vertColors[6];
	
	float locX;
	float locY;
	float prevX;
	float prevY;
	float velX;
	float velY;
	float vel;
	float angle;

	float randomJitterX;
	float randomJitterY;

	float diffX;
	float diffY;
	float diffAngle;
	float distRoot;
	float safeInv;
};


