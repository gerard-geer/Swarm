#include "Swarm.h"

Flies flies = Flies(NUM_FLIES);

/*
First render into offscreen.
Then use that data in X distort.
Then use that data in Y distort.
Then draw.
*/
GLFrameBuffer XDistort(WINDOW_WIDTH, WINDOW_HEIGHT, "X Gauss");
GLFrameBuffer YDistort(WINDOW_WIDTH, WINDOW_HEIGHT, "Y Gauss");
GLFrameBuffer offscreen(WINDOW_WIDTH/FBO_SCALE_FACTOR, WINDOW_HEIGHT/FBO_SCALE_FACTOR, "Offscreen");
GLFrameBuffer FullyBlurred(WINDOW_WIDTH, WINDOW_HEIGHT, "Post Gauss");

GLFrameBuffer motionBlurStore0(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 0");
GLFrameBuffer motionBlurStore1(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 1");
GLFrameBuffer motionBlurStore2(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 2");
GLFrameBuffer motionBlurStore3(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 3");
GLFrameBuffer motionBlurStore4(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 4");
GLFrameBuffer motionBlurStore5(WINDOW_WIDTH, WINDOW_HEIGHT, "Motion Blur 5");

FBOTexturedQuad xQuad(0, 0, 0, 1, 1);
FBOTexturedQuad yQuad(0, 0, 0, 1, 1);
FBOTexturedQuad finalQuad(0, 0, 0, 1, 1);

CompositeFBOQuad blooming(0, 0, 0, 1, 1);
CompositeFBOQuad motionBlurQuad(0, 0, 0, 1, 1);

bool mouseDown = false;
int mouseX = 0, mouseY = 0;
int frameCount = 0;

int main(int argc, char* argv[])
{
		
	initGlutWindow(argc, argv);

	/*GLenum bufs[2];
	bufs[0] = GL_FRONT_LEFT;
	bufs[1] = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(2, bufs);*/
	
	offscreen.initFrameBuffer(true);
	XDistort.initFrameBuffer(true);
	YDistort.initFrameBuffer(true);
	FullyBlurred.initFrameBuffer(true);

	motionBlurStore0.initFrameBuffer(true);
	motionBlurStore1.initFrameBuffer(true);
	motionBlurStore2.initFrameBuffer(true);
	motionBlurStore3.initFrameBuffer(true);
	motionBlurStore4.initFrameBuffer(true);
	motionBlurStore5.initFrameBuffer(true);
	

	xQuad.initFBOQuad(&offscreen, 0, "XGaussVert.glsl", "XGaussFrag.glsl", "Gaussian Blur X");
	yQuad.initFBOQuad(&XDistort, 0, "YGaussVert.glsl", "YGaussFrag.glsl", "Gaussian Blur Y");
	finalQuad.initFBOQuad(&YDistort, 0, "quadVert.glsl", "quadFrag.glsl", "Final blur shader");
	
	blooming.addFBO(&offscreen);
	blooming.addFBO(&FullyBlurred);
	blooming.initFBOQuad("bloomVert.glsl", "bloomFrag.glsl", "Composite Bloom Shader");

	motionBlurQuad.addFBO(&motionBlurStore0);
	motionBlurQuad.addFBO(&motionBlurStore1);
	motionBlurQuad.addFBO(&motionBlurStore2);
	motionBlurQuad.addFBO(&motionBlurStore3);
	motionBlurQuad.addFBO(&motionBlurStore4);
	motionBlurQuad.addFBO(&motionBlurStore5);
	motionBlurQuad.initFBOQuad("motionBlurVert.glsl", "motionBlurFrag.glsl", "Motion Blur Shader");
	
	//glViewport(60, 60, 100, 100);

	flies.initFlies("fliesVert.glsl", "fliesFrag.glsl", "Flies");
	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mousePressed);
	glutIdleFunc(display);
	printf("M_2_PI = %2f", M_PI);
	printf("WINDOW WIDTH: %2d\n", glutGet(GLUT_WINDOW_WIDTH));
	glutMainLoop();
	return exitDialog();
}

int exitDialog(void)
{
	printf("Program finished. Press enter to exit.");
	getchar();
	return 0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	offscreen.beginFBRendering();
	flies.renderFrame();
	offscreen.endFBRendering();

	XDistort.beginFBRendering();
	xQuad.render();
	XDistort.endFBRendering();

	YDistort.beginFBRendering();
	yQuad.render();
	YDistort.endFBRendering();

	FullyBlurred.beginFBRendering();
	finalQuad.render();
	FullyBlurred.endFBRendering();

	//xQuad.setFBO(&FullyBlurred);

	XDistort.beginFBRendering();
	xQuad.render();
	XDistort.endFBRendering();

	YDistort.beginFBRendering();
	yQuad.render();
	YDistort.endFBRendering();

	FullyBlurred.beginFBRendering();
	finalQuad.render();
	FullyBlurred.endFBRendering();

	if(frameCount%6 == 0)
	{
		motionBlurStore0.beginFBRendering();
		blooming.render();
		motionBlurStore0.endFBRendering();
	}
	if(frameCount%6 == 1)
	{
		motionBlurStore1.beginFBRendering();
		blooming.render();
		motionBlurStore1.endFBRendering();
	}
	if(frameCount%6 == 2)
	{
		motionBlurStore2.beginFBRendering();
		blooming.render();
		motionBlurStore2.endFBRendering();
	}
	if(frameCount%6 == 3)
	{
		motionBlurStore3.beginFBRendering();
		blooming.render();
		motionBlurStore3.endFBRendering();
	}
	if(frameCount%6 == 4)
	{
		motionBlurStore4.beginFBRendering();
		blooming.render();
		motionBlurStore4.endFBRendering();
	}
	if(frameCount%6 == 5)
	{
		motionBlurStore5.beginFBRendering();
		blooming.render();
		motionBlurStore5.endFBRendering();
	}

	motionBlurQuad.render();
	frameCount++;
	if(frameCount >100000){frameCount = 0;}
	if(mouseDown)
	{
		flies.gravitate(float(mouseX)/float(glutGet(GLUT_WINDOW_WIDTH)), float(mouseY)/float(glutGet(GLUT_WINDOW_HEIGHT)));
	}
	glutSwapBuffers();

	
}

void mouseMoved(int x, int y)
{
	mouseX = x;
	mouseY = y;
	flies.gravitate(float(x)/float(glutGet(GLUT_WINDOW_WIDTH)), float(y)/float(glutGet(GLUT_WINDOW_HEIGHT)));
}

void mousePressed(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		mouseX = x;
		mouseY = y;
		mouseDown = true;
	}
	else if(state == GLUT_UP)
	{
		mouseDown = false;
	}
}
