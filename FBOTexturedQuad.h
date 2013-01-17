#pragma once
#include "GLFrameBuffer.h"
#include "Shaders.h"
class FBOTexturedQuad
{
public:

	/*
	Constructs a new FBOTexturedQuad.

	Parameters:
		float locX:		The starting X location of the quad.
		float locY:		The starting Y location of the quad.
		float locZ:		The starting Z location of the quad.
		float width:	The starting width of the quad.
		float height:	The starting height of the quad.

	Returns:
		None

	*/
	FBOTexturedQuad(float locX, float locY, float locZ, float width, float height);

	/*
	Initializes the FBOQuad by giving it an FBO instance and also loads its shaders.
	All GPU-side initialization takes place here.
	GLEW MUST BE INITIALIZED, or equivalent.

	Parameters:
		GLFrameBuffer * fboInstance:	A pointer to texture the quad with.
		char * vertSource:	The filename of the vertex shader source code.
		char * fragSource:	The filename of the vertex shader source code.
		char * name:	The name to give the shader program.

	Returns:
		None

	*/
	void initFBOQuad(GLFrameBuffer * fboInstance, int textureUnit, char * vertSource, char * fragSource, char * name);
	
	/*
	Sets the location of the FBOquad anew.

	Parameters:
		float locX:		The new X location of the quad.
		float locY:		The new Y location of the quad.
		float locZ:		The new Z location of the quad.

	Returns:
		None

	*/
	void setLocation(float locX, float locY, float locZ);

	/*
	Sets the dimensions of the FBOquad.

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
	Destructs the FBOTexturedQuad. This especially deletes all shaders,
	buffers, and arrays from GPU memory.

	Parameters:
		None

	Returns:
		None
	*/
	~FBOTexturedQuad(void);

	/*
	Allows one to change the framebuffer that this quad samples.

	Parameters:
		GLFrameBuffer * newFBO:	The new GLFrameBuffer to sample during rendering.

	Returns:
		None
	*/
	void setFBO(GLFrameBuffer * newFBO);

private:

	/*
	A reference to the GLFrameBuffer that we will use to texture the quad.
	*/
	GLFrameBuffer * fbo;

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

