#include "Shaders.h"

/*
==============================================================================
SINGLE SHADER SINGLE SHADER SINGLE SHADER SINGLE SHADER SINGLE SHADER 
==============================================================================
*/
Shader::Shader(void)
{
	// In this case the constructor does nothing except initialize some
	// variables.
	filename = "";
	src = "";
	uiShader = 0;
	bLoaded = false;
	iType = 0;
}

Shader::~Shader(void)
{
	// The destructor just cleans up the GPU memory.
	deleteShader();
}


bool Shader::loadShader(char * sFile, int a_iType, bool extended) 
{ 
	// Store the filename.
	filename = sFile;

	// Store the type.
	iType = a_iType; 

	printf("================================================================\n");
	printf("%2s STATUS:\n", filename);
	printf("================================================================\n");

	// Load the file into a c-string.
	const GLchar * fileText;
	printf("LOADING SOURCE FILE [%2s]...\n", sFile);
	fileText = loadTextFile(sFile);
	if(fileText == 0){
		printf("COULD NOT LOAD SOURCE, USING FALLBACK BASIC SHADER.");
		if(a_iType == GL_VERTEX_SHADER){fileText = BASIC_VERT_SHADER;}
		else if(a_iType == GL_FRAGMENT_SHADER){fileText = BASIC_FRAG_SHADER;}
	}
	else printf("DONE LOADING SOURCE.\n");

	if(extended) src = fileText;
	else src = "SOURCE CODE NOT SAVED";
	 
	// Create a shader handle. This points to the location of the shader
	// in GPU (damn straight) memory. Essentially this is a gpu-malloc.
	printf("CREATING SHADER..\n");
	uiShader = glCreateShader(a_iType); 
	
	// This gives the GPU the source code of the shader, and binds it to
	// the program handle.
	printf("ATTACHING SHADER SOURCE..\n");
	glShaderSource(uiShader, 1, &fileText, NULL); 

	// This compiles the shader's source code into an executable that is
	// accessed through the shader handle.
	printf("COMPILING SHADER..\n");
	glCompileShader(uiShader); 
	
	// Now after we've told the shader to compile, we query the compilation status
	// of it.
	int iCompilationStatus; 
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus); 
	
	// If the shader failed to compile, we return false, after printing out
	// the status of the shader.	
	printf("================================================================\n");
	printf("%2s SUMMARY:\n", filename);
	printf("================================================================\n");

	if(iType == GL_FRAGMENT_SHADER)printf("TYPE: %2s\n", "FRAGMENT SHADER");
	else if(iType == GL_VERTEX_SHADER) printf("TYPE: %2s\n", "VERTEX SHADER");
	else printf("TYPE: %2s\n", "GEOMETRY SHADER");

	printf("SOURCE SIZE: %2d\n", strlen(fileText)*sizeof(char));
	
	if(iCompilationStatus == GL_FALSE)
	{
		printf("COMPILE: %2s\n", "FAILED");
		printf("ERROR: \n");
		GLint errorSize = 0;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &errorSize);
		char * errorLog = (char*)malloc((errorSize+1) * sizeof(char) );
		GLint actualsize = 0;
		glGetShaderInfoLog(uiShader, strlen(errorLog), &actualsize, errorLog);
		printf("%2s\n", errorLog);

	}
	else printf("COMPILE: %2s\n", "SUCCESS");
	printf("================================================================\n");


	if(iCompilationStatus == GL_FALSE)return false; 

	bLoaded = true; 
	
	return true; 
}

GLchar* Shader::loadTextFile(char* filename)
{
	
	// Create a file handle to use to read from the file.
	FILE *fileHandle;
	
	// Populate that file handle by opening into it the
	// file with the name given to us.
	// We open it with "rt" privledges, meaning that we 
	// can merely read it.
	printf("OPENING FILE...\n");
	fopen_s(&fileHandle, filename, "r");
	if(fileHandle == 0)
	{
		printf("...FILE COULD NOT BE OPENED.");
		return 0;
	}
	else printf("...FILE OPENED.\n");
	
	// Now we get the size of the file in bytes using fseek().
	// Move the pointer to the end of the file.
	printf("CHECKING FILE SIZE. \n\tseeking to end\n");
	fseek(fileHandle, 0, SEEK_END);
	
	printf("\tstoring location of pointer in bytes after fseek to end\n");
	// Now we can use the location of the pointer to tell the size of the file.
	long size = ftell(fileHandle);
	
	// Finally we return the carat back to the beginning of the file
	// for reading.
	printf("\treturning pointer to the original offset.\n");
	fseek(fileHandle, 0, SEEK_SET);
	
	// Create a string to hold the file's text.
	printf("\tcreating storage string.\n");
	char * fileContents = (char*) malloc ( size*sizeof(char) );
	
	fileContents[0] = 0;
		
	// Create a string to hold the current line.
	char line[80];
	
	// Load the lines from the file and concatenate them
	// into our storage string.
	printf("\tLoading file...\n");
	while(fgets(line, 80, fileHandle) != NULL){
		char * curLine = line;
		strncat_s(fileContents, size, curLine, 80);
	}
	
	printf("\"\tfile load complete.\n");
	return fileContents;
}

void Shader::printSource(void)
{
	printf("==SOURCE CODE===================================================\n");
	printf(src);
	printf("\n================================================================\n");
}

bool Shader::isLoaded(void)
{
	return bLoaded;
}

GLuint Shader::getShaderID(void)
{
	return uiShader;
}

char * Shader::getShaderType(void)
{
	if(iType == GL_VERTEX_SHADER)
	{
		return "GL_VERTEX_SHADER";
	}

	else if(iType == GL_FRAGMENT_SHADER)
	{
		return "GL_FRAGMENT_SHADER";
	}

	else
	{
		return "GL_GEOMETRY_SHADER";
	}
}

void Shader::deleteShader(void)
{
	printf("================================================================\n");
	printf("DELETING SHADER...\n");
	// If the shader was never loaded, return without trying to
	// access anything.
	if(!isLoaded())
	{
		printf("Shader never created!!!!!\n");
		printf("================================================================\n");
		return;
	}

	// Otherwise set the "loaded" boolean to false...
	bLoaded = false;

	// ...And tell OpenGL to delete the shader.
	glDeleteShader(uiShader);
	printf("Shader successfully deleted!!!!!\n");
	printf("================================================================\n");
}

/*
==============================================================================
 SHADER PROGRAM SHADER PROGRAM SHADER PROGRAM SHADER PROGRAM SHADER PROGRAM
==============================================================================
*/

ShaderProgram::ShaderProgram(void)
{
	// Just initializing stuff.
	programID = 0;
	linked = false;
	name = "*No name*";
}

ShaderProgram::ShaderProgram(char * programName)
{
	// Just initializing stuff.
	programID = 0;
	linked = false;
	name = programName;
}

ShaderProgram::~ShaderProgram(void)
{
	// Tell OpenGL to delete the shader to free some GPU memory.
	deleteProgram();
}

void ShaderProgram::createProgram(void)
{
	// Store the handle ID  to our new shader program
	// given to us by OpenGL.
	printf("\n\n================================================================\n");
	printf("CREATING RAW SHADER PROGRAM...\n");
	programID = glCreateProgram();
	printf("SUCCESS!\n");
	printf("==========\n");
	printf("ID: %2d\n", getProgramID());
	printf("NAME: %2s\n", getName());
	printf("============================================\n");
}

bool ShaderProgram::attachShaderToProgram(Shader * shader)
{
	if(programID == 0)
	{
		printf("============================================\n");
		printf("ATTACHING SHADER TO PROGRAM...\n");
		printf("ERROR: SHADER PROGRAM NOT CREATED YET.\n");
		printf("NAME: %2s\n", getName());
		printf("============================================\n");
		return false;
	}
	else if(!shader->isLoaded())
	{
		printf("============================================\n");
		printf("ATTACHING SHADER TO PROGRAM...\n");
		printf("ERROR: SHADER NOT LOADED.\n");
		printf("NAME: %2s\n", getName());
		printf("============================================\n");
		return false;
	}
	else
	{
		printf("============================================\n");
		printf("ATTACHING SHADER TO PROGRAM...\n");
		glAttachShader(programID, shader->getShaderID() );
		printf("==========\n");
		printf("ID: %2d\n", getProgramID());
		printf("NAME: %2s\n", getName());
		printf("==========\n");
		printf("SHADER ID: %2d\n", shader->getShaderID());
		printf("TYPE: %2s\n", shader->getShaderType());
		printf("============================================\n");
		return true;
	}
}

bool ShaderProgram::linkProgram(void)
{
	printf("============================================\n");
	printf("%2s SHADER PROGRAM STATUS: \n", name);
	printf("ID: %2d\n", getProgramID());
	printf("==========\n");
	printf("Linking program...\b\n");
	// Tell OpenGL to try to link the various shaders added to this
	// program into a pipeline.
	glLinkProgram(programID);
	printf("==========\n");
	printf("LINK ATTEMPT COMPLETE.\n");

	// Get the link status of the attempt.
	int iLinkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &iLinkStatus);
	linked = iLinkStatus == GL_TRUE;
	printf("LINK STATUS: %2d\n", linked);
	printf("================================================================\n");

	// Return that link status.
	return linked;
}

void ShaderProgram::deleteProgram(void)
{
	printf("================================================================\n");
	printf("DELETING SHADER PROGRAM [%2s]...\n", name);
	// Don't do anything if we haven't linked the shader program.
	if(!isLinked())
	{
		printf("PROGRAM NOT LINKED. Deleting anyway...\n");
		glDeleteProgram(programID);
		printf("...Program deleted.\n");
		printf("================================================================\n");
		return;
	}

	// If we have, reset the variable...
	linked = false;
	// ... and tell OpenGL to delete the program.
	glDeleteProgram(programID);
	printf("...Program deleted.\n");
	printf("================================================================\n");
}

void ShaderProgram::useProgram(void)
{
	// If the program is linked, tell openGL to use the program.
	if(isLinked()) glUseProgram(programID);
}

void ShaderProgram::stopUsingProgram(void)
{
	//Tell OpenGL to not use any program.
	glUseProgram(0);
}

GLuint ShaderProgram::getProgramID(void)
{
	return programID;
}

bool ShaderProgram::isLinked(void)
{
	return linked;
}

void ShaderProgram::setName(char * newName)
{
	name = newName;
}

char * ShaderProgram::getName(void)
{
	return name;
}





