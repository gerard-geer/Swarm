#include "Flies.h"


Flies::Flies(int amount)
{
	// Generate the flies.
	for(int i = 0; i < amount; i++)
	{
		flies.push_back(Fly());
	}
	
}

void Flies::initFlies(char * vert, char * frag, char * name)
{
	// Generate handles to GPU-side buffers.
	// A vertex array holds all the information about a set of
	// vertices, which is stored as vertex buffer objects.
	glGenVertexArrays(1, &vertexArray);
	printf("Generated vertex array.\n");
	glGenBuffers(2, vboHandles);
	printf("Generated vertex buffers.\n");

	// Load in the vertex shader that was specified.
	vertex.loadShader(vert, GL_VERTEX_SHADER, true);
	vertex.printSource();
	
	// Do the same with the fragment shader.
	fragment.loadShader(frag, GL_FRAGMENT_SHADER, true);
	fragment.printSource();

	// Link the two into a shader program.
	shader.setName(name);
	shader.createProgram();
	shader.attachShaderToProgram(&vertex);
	shader.attachShaderToProgram(&fragment);
	shader.linkProgram();

	// Now that we've generated our vertex array, let's bind to it,
	// meaning that any vertex buffer operations will be done on this one.
	glBindVertexArray(vertexArray);
	printf("Bound to vertex array.\n");
	// By that we've told OpenGL that we are going to use our specific
	// vertex array. Now let's give it some info on those verts.
	//
	// First we generate a vertex array of the flies locations.
	float * vertDataArray = createVertLocDataArray();

	// Next let's bind to our first array.
	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
	// Now let's give it the vertex data.
	glBufferData(GL_ARRAY_BUFFER, flies.size() * 6 * sizeof(float), vertDataArray, GL_DYNAMIC_DRAW);
	// Enable it for use.
	glEnableVertexAttribArray(0);
	// And now we set up some shit.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Clean up that memory.
	free((void*)vertDataArray);
	
	// Now we get to do it all again with the color buffer.
	float * colorDataArray = createVertColorDataArray();
	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[1]);
	glBufferData(GL_ARRAY_BUFFER, flies.size() * 6 * sizeof(float), colorDataArray, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	free((void *)colorDataArray);
}


Flies::~Flies(void)
{
	vertex.deleteShader();
	fragment.deleteShader();
	shader.deleteProgram();
}

void Flies::renderFrame(void)
{
	// Start using our shader program.
	shader.useProgram();

	// Pass the current elapsed time into our shader.
	float time = float(glutGet(GLUT_ELAPSED_TIME));
	time/=10000.0f;

	GLuint sampleLoc = 99;
	sampleLoc = glGetUniformLocation(shader.getProgramID(), "time\0");
	glUniform1f(sampleLoc, time);
	
	

	// Bind to our vertex array in case it lost focus.
	glBindVertexArray(vertexArray);

	// Actually draw the vertex array.
	for( unsigned int i = 0; i < flies.size(); i ++)
	{
		glDrawArrays(GL_LINES, i*2, 2);
	}

	// Update everything about each of the flies.
	for(unsigned int i = 0; i < flies.size(); i ++)
	{
		flies[i].handle();
		flies[i].render();
	}

	// Now we bind to the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);

	// Next we create a copy of all the vertex data.
	float * vertData = createVertLocDataArray();

	// Now we sub in our new data to the graphics card.
	glBufferSubData(GL_ARRAY_BUFFER, 0, flies.size() * 6 * sizeof(float), vertData);

	// Finally we free the memory used in the operation.
	free((void*)vertData);

    // Now we do the same with the color buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[1]);
	float * colorData = createVertColorDataArray();
	glBufferSubData(GL_ARRAY_BUFFER, 0, flies.size() * 6 * sizeof(float), colorData);
	free((void*)colorData);

	// Tell OpenGL to stop using our shader program.
	shader.stopUsingProgram();

	// Bind back to the null vertex array.
	glBindVertexArray(0);

	
	
		
}

float * Flies::createVertLocDataArray(void)
{
	// Generate a vertex array of the flies locations.
	float * vertDataArray = 0;
	vertDataArray = (float*)malloc(sizeof(float)*flies.size()*6);
	if(vertDataArray == 0){printf("OH SHIT OH SHIT\n");}
	for(unsigned int i = 0; i < flies.size(); i++)
	{
		for(int k = 0; k < 6; k++)
		{
			vertDataArray[(i * 6) + k] = flies[i].vertLocations[k];
		}
	}

	return vertDataArray;
}

float * Flies::createVertColorDataArray(void)
{
	// Generate a vertex array of the flies locations.
	float * vertDataArray = 0;
	vertDataArray = (float*)malloc(sizeof(float)*flies.size()*6);
	if(vertDataArray == 0){printf("OH SHIT OH SHIT\n");}
	for(unsigned int i = 0; i < flies.size(); i++)
	{
		for(int k = 0; k < 6; k++)
		{
			vertDataArray[(i * 6) + k] = flies[i].vertColors[k];
		}
	}

	return vertDataArray;
}

void Flies::gravitate(float x, float y)
{
	// Tell all the flies to gravitate towards this point.
	for(int i = 0; i < flies.size(); i++)
	{
		flies[i].gravitate(x, y);
	}
}
