#pragma once

#include "GLFrameBuffer.h"
#include "Shaders.h"
#include <vector>
#include <sstream>

class CompositeFBOQuad
{
public:

	/*
	Constructs a new CompositeFBOQuad.

	Parameters:
		float locX:		The starting X location of the quad.
		float locY:		The starting Y location of the quad.
		float locZ:		The starting Z location of the quad.
		float width:	The starting width of the quad.
		float height:	The starting height of the quad.

	Returns:
		None

	*/
	CompositeFBOQuad(float locX, float locY, float locZ, float width, float height);

	/*
	Initializes the CompositeFBOQuad by loading its shaders.
	This is different from the other FBOQuad, as here you need to add FBOs one
	at a time.
	Also notice how we don't allow the specification of a texture unit.
	That is because we need to consume multiple texture units so that we
	can composite all the various FBOs.

	GLEW MUST BE INITIALIZED, or equivalent.

	Parameters:
		char * vertSource:	The filename of the vertex shader source code.
		char * fragSource:	The filename of the vertex shader source code.
		char * name:	The name to give the shader program.

	Returns:
		None

	*/
	void initFBOQuad(char * vertSource, char * fragSource, char * name);

	/*
	Adds a GLFrameBuffer to this CompositeFBOQuad.

	Parameters:
		GLFrameBuffer * newFBO:		The FBO to add to this CompositeFBOQuad.

	Returns:
		None

	*/
	void addFBO(GLFrameBuffer * newFBO);
	
	/*
	Sets the location of the CompositeFBOQuad anew.

	Parameters:
		float locX:		The new X location of the quad.
		float locY:		The new Y location of the quad.
		float locZ:		The new Z location of the quad.

	Returns:
		None

	*/
	void setLocation(float locX, float locY, float locZ);

	/*
	Sets the dimensions of the CompositeFBOQuad.

	Parameters:
		float width:	The new width of the quad.
		float height:	The new height of the quad.

	Returns:
		None
	*/
	void setDimensions(float width, float height);

	/*
	Draws the quad to the screen.

	Parameters:
		None

	Returns:
		None
	*/
	void render(void);

	/*
	Destructs the CompositeFBOQuad. This especially deletes all shaders,
	buffers, and arrays from GPU memory.

	Parameters:
		None

	Returns:
		None
	*/
	~CompositeFBOQuad(void);

private:

	/*
	A vector of the various FBOs that make up the image of this quad.
	*/
	std::vector<GLFrameBuffer * > fbos;

	/*
	A vector to store the preformatted sampler names.
	*/
	std::vector<char * > samplerNames; 

	/*
	OpenGL's ID for the vertex array used to address the vertex components.
	*/
	GLuint vertexArray;

	/*
	OpenGL's ID for the sampler that we use to pass the FBO's texture to the 
	shaders.
	*/
	GLuint sampler;

	/*
	The texture unit that we use for the quad's texture.
	*/
	int tUnit;

	/*
	The shader program used to draw the quad.
	*/
	ShaderProgram shaderProgram;

	/*
	The fragment component of the shader program.
	*/
	Shader frag;

	/*
	The vertex component of the shader program.
	*/
	Shader vert;

	/*
	OpenGL's IDs for the vertex buffers that we use to store the vertex locations
	and their UV coordinates.
	*/
	GLuint vboHandles[2];

	/*
	The X location of the quad.
	*/
	float x;

	/*
	The Y location of the quad.
	*/
	float y;

	/*
	The Z location of the quad.
	*/
	float z;

	/*
	The width of the quad.
	*/
	float w;

	/*
	The height of the quad.
	*/
	float h;

	/*
	Updates the vertex component buffers on the GPU.
	*/
	void updateVerts(void);
	

};

