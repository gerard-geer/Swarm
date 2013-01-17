#include "GlutFunctions.h"

bool fullScreen = false;

void keyPressed( unsigned char key, int x, int y)
{
	if(key == 27){exit((int)0);}
	if(key == 13)
	{
		if(glutGetModifiers() == GLUT_ACTIVE_ALT)
		{
			if(!fullScreen){
				glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
				glutFullScreen();
				printf("New window width: %d\n", glutGet(GLUT_WINDOW_WIDTH));
				printf("New window height: %d\n", glutGet(GLUT_WINDOW_HEIGHT));
				printf("SCREEN width: %d\n", glutGet(GLUT_SCREEN_WIDTH));
				printf("SCREEN height: %d\n", glutGet(GLUT_SCREEN_HEIGHT));
				fullScreen = true;
			}
			else{
				glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
				glutPositionWindow(WINDOW_X, WINDOW_Y);
				fullScreen = false;
			}
		}
	}
}

void specialPressed( int key, int x, int y)
{
	if(key == GLUT_KEY_F4 && glutGetModifiers() == GLUT_ACTIVE_ALT)
	{
		exit(9000);
	}
}



void initGlutWindow(int argc, char ** argv)
{
	// We don't start full screen.
	fullScreen = false;

	// Initialize GLUT.
	glutInit(&argc,argv);
	
	// Initialize the display mode to be RGB and double buffered,
	// and have an active depth buffer.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 

	// Set the initial window size.
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Set the initial window position.
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);

	// Create the window.
	glutCreateWindow("Swarm by Gerard Geer"); 

	// Now and ONLY NOW can we initialize glew.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
	}
	else printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


	// Set the background color.
	glClearColor(0, 0, 0, .001f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// FUCKING ENABLE DEPTH TESTING.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Enable texturing.
	glEnable(GL_TEXTURE_2D);

	// Make the lines fatter.
	//glLineWidth(3.0f);
	
	// Set up the projection matrix.
	//gluOrtho2D(0, 1, 1, 0);

	// Register a bunch of callbacks.
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialPressed);
	
	// Tell the user that the window is finished being made.
	printf("Finished initializing window.\n");
}

