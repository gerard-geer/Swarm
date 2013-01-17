#include "GLTexture.h"


GLTexture::GLTexture(void)
{
}


GLTexture::~GLTexture(void)
{
	deleteTexture();
}

void GLTexture::createEmptyTexture(int width, int height, GLenum format)
{
	w = width;
	h = height;

	// Generate our texture ID.
	glGenTextures(1, &texture);

	// Generate a sampler ID.
	glGenSamplers(1, &sampler);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	// The internal format of a texture should not be out of order (BGRA), so 
	// we intercept those here.
	if(format == GL_RGBA || format == GL_BGRA)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
	else if(format == GL_RGB || format == GL_BGR)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
}

void GLTexture::bindTexture(int textureUnit)
{
	// Make the texture unit <TextureUnit> the active texture, meaning that all
	// subsequent texture calls, such as glBindTexture() will affect this
	// texture unit.
	glActiveTexture(GL_TEXTURE0+textureUnit);

	// Bind our texture to the GL_TEXTURE_2D target of our active texture unit.
	glBindTexture(GL_TEXTURE_2D, texture);

	// We also bind our sampler to this texture unit so that we can access
	// this texture within shaders.
	glBindSampler(textureUnit, sampler);

}

void GLTexture::setFiltering(GLenum mag, GLenum min)
{
	// Bind to our sampler so that we can edit the interpolation attributes.
	// We bind it to the 0th textre target since we don't need it to be attached
	// to a texture unit to edit its properties.
	glBindSampler(0, sampler);

	// Set the magnification and minifcation filters.
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, mag);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, min);
}

void GLTexture::setSamplerParameter(GLenum parameter, GLenum value)
{
	// This one is a straight pass-through.
	glSamplerParameteri(sampler, parameter, value);
}

void GLTexture::deleteTexture(void)
{
	// Deletes the texture object from GPU memory if it ever existed.
	if(sampler != 0) glDeleteSamplers(1, &sampler);

	// Deletes the sampler object from GPU memory if it ever existed.
	if(texture != 0) glDeleteTextures(1, &texture);
}

GLuint GLTexture::getTextureID(void)
{
	return texture;
}

GLuint GLTexture::getSamplerID(void)
{
	return sampler;
}

int GLTexture::getWidth(void)
{
	return w;
}

int GLTexture::getHeight(void)
{
	return h;
}



