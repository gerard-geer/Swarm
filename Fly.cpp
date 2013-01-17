#include "Fly.h"

Fly::Fly(void)
{
	locX = (float(rand())/float(RAND_MAX));
	locY = (float(rand())/float(RAND_MAX));
	prevX = locX;
	prevY = locY;

	vertLocations[0] = locX;
	vertLocations[1] = locY;
	vertLocations[2] = prevX;
	vertLocations[3] = prevY;

	for(int i = 0; i < 2; i++){
		vertColors[3*i] = .02f;	// R
		vertColors[3*i+1] = .02f; // G
		vertColors[3*i+2] = .02f; // B
	}
	// Radians.
	angle = (float(rand())/float(RAND_MAX))*2.00f*M_PI;
	vel = (.005f * (float(rand())/float(RAND_MAX)))-.0025f;
	velX = vel * sin(angle);
	velY = vel * cos(angle);
}

Fly::Fly(float x, float y, float velocity, float newAngle)
{
	// Store location.
	locX = x;
	locY = y;
	prevX = locX+1;
	prevY = locY+1;

	// Store the location variables in an array for OpenGL.
	vertLocations[0] = locX;
	vertLocations[1] = locY;
	vertLocations[2] = -.5f;
	vertLocations[3] = prevX;
	vertLocations[4] = prevY;
	vertLocations[5] = -.5f;

	// Poop in some color vars.
	for(int i = 0; i < 2; i++){
		vertColors[3*i] = .02f * vel;	// R
		vertColors[3*i+1] = .02f * vel; // G
		vertColors[3*i+2] = .02f * vel; // B
	}

	/*
	Create a starting velocity from a random angle.
	*/
	angle = (float(rand())/float(RAND_MAX))*2.00f*M_PI; // Radians.
	vel = velocity;

	angle = newAngle;

	velX = vel * sin(angle);
	velY = vel * cos(angle);
}


Fly::~Fly(void)
{
}

void Fly::handle(void)
{
	// Store the current location in the previous location.
	// We store along with it a small value so that the lines never fully
	// disappear.
	prevX = locX+.001;
	prevY = locY-.001;

	// Grade down the velocity.
	vel *= .985f;

	// We create some random jitter so that the particles move uniquely.
	randomJitterX = (((float(rand())/float(RAND_MAX))*.002f)-.001f) * 1/((vel+.001f)*100);
	randomJitterY = (((float(rand())/float(RAND_MAX))*.002f)-.001f) * 1/((vel+.001f)*100);
	velX = ((vel+randomJitterX) * cos(angle));
	velY = ((vel+randomJitterY) * sin(angle));

	// Screen wrapping. 
	if(locX > 1)
	{
		locX = 0;
		prevX = locX;
	}
	else if(locX < 0)
	{
		locX = 1;
		prevX = locX;
	} 
	
	if(locY > 1)
	{
		locY = 0; 
		prevY = locY;
	}
	else if(locY < 0)
	{
		locY = 1;
		prevY = locY;
	} 

	locX += velX;
	locY += velY;

	//if(abs(vel)>.00001f)angle = atan2(velY, velX);
	//if(abs(vel)>.061f)vel = .001f;
	if(angle >= 2.00f*M_PI) angle -= 2.00f*M_PI;
	else if(angle < 0) angle += 2.00f*M_PI;
}

void Fly::render(void)
{
	vertLocations[0] = locX;
	vertLocations[1] = locY;
	vertLocations[2] = -0;
	vertLocations[3] = prevX;
	vertLocations[4] = prevY;
	vertLocations[5] = -0;
	}

void Fly::gravitate( float x, float y ) {
    diffX = -(locX-x);
    diffY = -(locY-y);

	angle = atan2(diffY/2, diffX/2);

	distRoot = sqrt( pow(diffX, 2) + pow(diffY, 2) );
	safeInv = 1.0f/(distRoot+1.5f);
	vel += .0005f*pow(safeInv, 1);
}