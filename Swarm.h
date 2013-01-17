#include <stdio.h>
#include <iostream>
#include "Const.h"
#include "Flies.h"
#include "Shaders.h"
#include "GLFrameBuffer.h"
#include "FBOTexturedQuad.h"
#include "CompositeFBOQuad.h"
#include "GlutFunctions.h"

int exitDialog(void);
void display(void);
void mouseMoved(int x, int y);
void mousePressed(int button, int state, int x, int y);
void mouseReleased(void);