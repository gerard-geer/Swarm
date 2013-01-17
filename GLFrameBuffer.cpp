#include "GLFrameBuffer.h"


GLFrameBuffer::GLFrameBuffer(int width, int height, char * newName)
{
	fbo = 0;
	fbo_depth = 0;
	w = width;
	h = height;
	name = newName;
	initialized = false;
}


GLFrameBuffer::~GLFrameBuffer(void)
{
	deleteFrameBuffer();
}

void GLFrameBuffer::initDepthBuffer(void)
{
	if(fbo == 0) return;
	// Bind to the renderbuffer so that we can edit it.
	printf("\tBinding to renderbuffer...\n");
	glBindRenderbuffer(GL_RENDERBUFFER, fbo_depth); 

	// Generate one renderbuffer and store its ID in fbo_depth.
	printf("\tGenerating Depth buffer ID...\n");
	glGenRenderbuffers(1, &fbo_depth);
	printf("\tDepth Buffer ID: %2d\n", fbo_depth);
	

	// Set up the storage medium of the renderbuffer to be the correct size.
	printf("\tFormatting renderbuffer memory..\n");
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);

	// Set the render buffer of our framebuffer to be a dpeth buffer.
	printf("\tSetting up renderbuffer...\n");
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo_depth);

	// Bind to a 0 renderbuffer.
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void GLFrameBuffer::initFrameBuffer(bool depthbuffer)
{
	// Generate a frame buffer and store the ID in fbo.
	printf("Organizing framebuffer elements...\n");
	glGenFramebuffers(1, &fbo);
	printf("FBO ID: %2d\n", fbo);

	// Bind to that frame buffer so that we can edit it.
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//glClearColor(0, 0, .125f, 1);

	printf("================================================================\n");
	printf("FRAMEBUFFER [%2s] STATUS:\n", name);

	// Initialize the texture that we will be rendering into.
	printf("initializing texture to render to...\n");	
	
	texture.createEmptyTexture(w, h, GL_RGBA);
	texture.setFiltering(GL_NEAREST, GL_NEAREST);
	texture.setSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	texture.setSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	texture.setSamplerParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Attach the texture we set up to be the color buffer of our framebuffer.
	printf("Binding color buffer (texture) to framebuffer.\n");
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTextureID(), 0);

	// Initialize the depth buffer of this framebuffer.
	if(depthbuffer)
	{
		printf("initializing depth buffer...\n");
		initDepthBuffer();
	}
	else printf("NOTE: NO DEPTH COMPONENT...\n");	

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR: Could not create framebuffer.\n");
		printf("ERROR CODE: 0x%2x\n", status);
	}
	else
	{
		printf("FRAMEBUFFER COMPLETE!!\n");
		initialized = true;
	}

	printf("NAME: %2s\n", name);
	printf("WIDTH: %2d\n", w);
	printf("HEIGHT: %2d\n", h);
	printf("================================================================\n");

	// Unbind from the framebuffer so that it doesn't immediately go into use.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::deleteFrameBuffer(void)
{
	if(fbo_depth != 0)	glDeleteRenderbuffers(1, &fbo_depth);
	else printf("%2s FBO depth buffer never created.", name);
	if(fbo != 0) glDeleteFramebuffers(1, &fbo);
	else printf("%2s framebuffer never created.", name);
	texture.deleteTexture();

	initialized = false;
}

void GLFrameBuffer::beginFBRendering(void)
{
	// Bind to the framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Clear the previous data.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, w, h);
}

void GLFrameBuffer::endFBRendering(void)
{
	// Pop the attribute.
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	// Bind the framebuffer back to 0, meaning all rendering
	// calls are drawn to the screen directly.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int GLFrameBuffer::getFBO(void)
{
	return fbo;
}

unsigned int GLFrameBuffer::getFBODepth(void)
{
	return fbo_depth;
}

GLTexture * GLFrameBuffer::getFBOTexture(void)
{
	return &texture;
}

int GLFrameBuffer::getHeight(void)
{
	return h;
}

int GLFrameBuffer::getWidth(void)
{
	return w;
}

char ** GLFrameBuffer::getName(void)
{
	return &name;
}

bool GLFrameBuffer::isInitialized(void)
{
	return initialized;
}









