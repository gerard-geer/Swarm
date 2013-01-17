#pragma once

#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glut.h>
#include <stdio.h>
#include "GLTexture.h"
#include "Const.h"
class GLFrameBuffer
{
public:

	/*
	Constructs a new GLFrameBuffer.

	Parameters:
		width: The horizontal resolution of this framebuffer.
		height: The vertical resolution of this framebuffer.
		newName: The name of this framebuffer; useful for debug-output identification.
			This defaults to "*No name*".
	*/
	GLFrameBuffer(int width, int height, char * newName = "*No name*");

	/*
	Destructs the GLFramebuffer, and deletes all traces of it from GPU memory as well.
	*/
	~GLFrameBuffer(void);

	/*
	Initializes the Framebuffer within OpenGL and GPU memory. This must be called
	AFTER glew is initialized, otherwise a segfault will occur.

	Parameters:
		depthbuffer: Whether or not to include a depth buffer with this framebuffer.
	*/
	void initFrameBuffer(bool depthbuffer);

	/*
	Deletes the Framebuffer and all associated elements from GPU memory.
	*/
	void deleteFrameBuffer(void);

	/*
	Makes this GLFramebuffer the current rendering context.
	All subsequent rendering calls before the next call to endFBRendering(void)
	will draw into this framebuffer.
	*/
	void beginFBRendering(void);

	/*
	Removes this framebuffer as the current rendering context, making all
	subsequent rendering calls before the next call to beginFBRendering(void)
	not draw to this framebuffer, but either to the screen directly or to
	another framebuffer.
	*/
	void endFBRendering(void);

	/*
	Returns OpenGL's ID for this framebuffer object.
	*/
	unsigned int getFBO(void);

	/*
	Returns OpenGL's ID for the depth buffer of this framebuffer.
	*/
	unsigned int getFBODepth(void);

	/*
	Returns OpenGL's ID for the texture that is rendered to by
	this framebuffer.
	*/
	GLTexture * getFBOTexture(void);

	/*
	Returns the vertical resolution of this framebuffer.
	*/
	int getHeight(void);
	
	/*
	Returns the horizontal resolution of this framebuffer.
	*/
	int getWidth(void);

	/*
	Returns the name of this framebuffer.
	*/
	char ** getName(void);

	/*
	Returns whether or not this framebuffer has been successfully initialized.
	*/
	bool isInitialized(void);
	
private:

	/*
	Initializes the depth buffer of this FBO.
	*/
	void initDepthBuffer(void);

	/*
	OpenGL's ID for the actual FBO in GPU memory.
	*/
	GLuint fbo;

	/*
	OpenGL's ID for the depth buffer of this FBO.
	*/
	GLuint fbo_depth;

	/*
	The GLTexture that is used as the FBO's texture.
	*/
	GLTexture texture;
	
	/*
	The width of this framebuffer.
	*/
	int w;

	/*
	The height of this framebuffer.
	*/
	int h;

	/*
	Whether or not this FBO is initialized fully.
	*/
	bool initialized;

	/*
	An optional name for this FBO to use during debug output.
	*/
	char * name;

};

