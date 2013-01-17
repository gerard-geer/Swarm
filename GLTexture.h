#pragma once
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glut.h>
#include <stdio.h>
class GLTexture
{
public:

	/*
	Constructs the GLTexture.

	Parameters:
		None

	Returns:
		None
	*/
	GLTexture(void);

	/*
	Destructs the GLTexture. Here we clear GPU memory as well.

	Parameters:
		None

	Returns:
		None
	*/
	~GLTexture(void);

	/*
	Creates an empty GLTexture. This means that the texture,
	well, has no image data in it.

	Parameters:
		int width:	The width of the new texture in memory.
			All OpenGL implementations support a width of at least
			1024 pixels/texels.
		int height:	The height of this new texture.
			All OpenGL implementations support a height of at least
			1024 pixels/texels.
		GLenum format:	The format of the texture. Use Google if you aren't
			using GL_RGB or GL_RGBA.

	Returns:
		None
	*/
	void createEmptyTexture(int width, int height, GLenum format);

	/*
	Binds the texture to the specified texture target, then
	binds this GLTexture's sampler to the target as well.

	Parameters:
		int textureUnit (default of 0): The texture unit to bind to.
			All OpenGL implementations support at least 80 
			texture units.

	Returns:
		None.
	*/
	void bindTexture(int textureUnit = 0);

	/*
	Sets the filtering model not of the texture itself, but of its sampler
	object. This allows the texture to be un adulterated and to be used
	equally in multiple instances.

	Parameters:
		GLenum mag:	The value to set GL_TEXTURE_MAG_FILTER to.
		GLenum min:	The value to set GL_TEXTURE_MIN_FILTER to.

	Returns:
		None
	*/
	void setFiltering(GLenum mag, GLenum GLenum);

	/*
	Sets the given sampler parameter to the given value.

	Parameters:
		GLenum parameter:	The parameter to edit.
		GLenum value:	The value to assign to the parameter.
	*/
	void setSamplerParameter(GLenum parameter, GLenum value);

	/*
	Deletes the textures from GPU memory.

	Parameters:
		None

	Returns:
		None
	*/
	void deleteTexture(void);

	/*
	Returns OpenGL's ID for the texture component of this GLTexture.

	Parameters:
		None

	Returns:
		OpenGL's ID for the texture component of this GLTexture.
	*/
	GLuint getTextureID(void);

	/*
	Returns OpenGL's ID for the sampler component of this GLTexture.

	Parameters:
		None

	Returns:
		OpenGL's ID for the sampler component of this GLTexture.
	*/
	GLuint getSamplerID(void);

	/*
	Returns the width of this texture.
	
	Parameters:
		None
		
	Returns:
		The width of this GLTexture.
	*/
	int getWidth(void);

	/*
	Returns the height of this texture.
	
	Parameters:
		None
		
	Returns:
		The height of this GLTexture.
	*/
	int getHeight(void);
private:

	/*
	The width of this texture.
	*/
	int w;

	/*
	The height of this texture.
	*/
	int h;

	/*
	The ID given by OpenGL to refer to the texture component
	of this GLTexture in GPU memory.
	*/
	GLuint texture;

	/*
	The ID given by OpenGL to refer to the sampler component
	of this GLTexture in GPU memory.
	*/
	GLuint sampler;
};

