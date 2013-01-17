#pragma once
#include <iostream>
#include <vector>
#include <glew.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <GL\GL.h>

class Shader 
{ 
public:

	/*
	Constructs the shader.

	Parameters:
		None
	*/
	Shader(void);

	/*
	Destructs the shader. Here we clean up GPU memory.

	Parameters:
		None
	*/
	~Shader(void); 

	/*
	Loads a text file and returns it as a GLchar string.

	Parameters:
		char * filename - The relative name and path of the file.

	Returns:
		A GLchar string that contains the text of the file.
	*/
	GLchar* loadTextFile(char* filename); 

	/*
	Loads the shader into GPU memory.

	Parameters:
		char * sFile - The name of the file and path for loading.
		int a_iType - The type of shader we are working with.
		bool extended = false - Whether or not to store extended debug info, such as
			the source code of the shader.
	Returns:
		Whether or not the shader was compiled successfully.
	*/
	bool loadShader(char * sFile, int a_iType, bool extended = false); 

	/*
	Deletes the shader from GPU memory.

	Parameters:
		None
	*/
	void deleteShader(void);

	/*
	Prints the source code of the shader, should extended debugging be enabled.

	Parameters:
		None
	*/
	void printSource(void);

	/*
	Returns whether or not the shader is loaded.

	Parameters:
		None

	Returns:
		Whether or not the shader was properly loaded.
	*/
	bool isLoaded(void); 

	/*
	Returns the GPU's ID of the shader.

	Parameters:
		None

	Returns:
		OpenGL's ID for the shader.
	*/
	GLuint getShaderID(void); 

	/*
	Returns the the type of the shader as a string.

	Parameters:
		None

	Returns:
		The shader type.
	*/
	char * getShaderType(void); 
	
private: 

	/*
	The ID given to the shader by OpenGL for reference during
	compile and use.
	*/
	unsigned int uiShader; 

	/*
	The shader type, meaning what stage it represents in the
	rendering pipeline. E.g.:
	GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER
	*/
	int iType;

	/*
	A boolean that flags whether or not the shader was successfully
	loaded.
	*/
	bool bLoaded;

	/*
	The filename of the source file, stored for debug reference.
	*/
	char * filename;

	/*
	When TRUE is passed as the third argument of loadShader(),
	the entire source of the shader is stored in memory, within
	this string.
	*/
	const GLchar * src;
};

class ShaderProgram
{
public:

	/*
	Constructs the Shader program. We just initialize some things here.

	Parameters:
		None
	*/
	ShaderProgram(void);

	/*
	Constructs the Shader program. We just initialize some things here.

	Parameters:
		char * programName - A name to give the shader program.
	*/
	ShaderProgram(char * programName);

	/*
	Destructs the shader program, making sure to clear GPU memory.

	Parameters:
		None
	*/
	~ShaderProgram(void);

	/*
	Creates a shader program. Shader programs are the full pipeline worth
	of shaders. This generates a pointer to an empty, unlinked program and
	stores it.

	Parameters:
		None

	Returns:
		None
	*/
	void createProgram(void);

	/*
	This deletes the program.

	Parameters:
		None

	Returns:
		None
	*/
	void deleteProgram(void);

	/*
	This adds a shader in the form of a Shader object to the pipeline.

	Parameters:
		Shader * shader - A pointer to a Shader object that was successfully
			created and compiled.

	Returns:
		Whether or not the shader was attached.
	*/
	bool attachShaderToProgram(Shader * shader);

	/*
	Links all the shaders into a single pipeline that can be used during
	rendering.

	Parameters:
		None

	Returns:
		Whether or not the program linked.
	*/
	bool linkProgram(void);

	/*
	Tells OpenGL to use the program to define the rendering pipeline used
	to draw geometry for the time-being.

	Parameters:
		None

	Returns:
		None
	*/
	void useProgram(void);

	/*
	Tells OpenGL to stop using this program to define the rendering pipeline.

	Parameters:
		None

	Returns:
		None
	*/
	void stopUsingProgram(void);

	/*
	Returns the ID of the program for debug use.

	Parameters:
		None

	Returns:
		OpenGL's ID for the shader program.
	*/
	GLuint getProgramID(void);

	/*
	Returns whether or not the shader linked properly.

	Parameters:
		None

	Returns:
		Whether or not the program is linked.
	*/
	bool isLinked(void);

	/*
	Sets the name of the Shader Program.

	Parameters:
		char * newName: The new name to give the shader program.

	Returns:
		None.
	*/
	void setName(char * newName);

	/*
	Returns the name of this shader program.

	Parameters:
		None

	Returns:
		The name of this shader program.
	*/
	char * getName(void);


private:

	/*
	A name that can be used to identify this shader program.
	*/
	char * name;

	/*
	OpenGL's ID for the program.
	*/
	unsigned int programID;

	/*
	Whether or not the shader is linked.
	*/
	bool linked;
};

#define BASIC_VERT_SHADER "#version 140 uniform Transformation { mat4 projection_matrix; mat4 modelview_matrix; }; in vec3 vertex; void main() { gl_Position = projection_matrix * modelview_matrix * vec4(vertex, 1.0);}"
#define BASIC_FRAG_SHADER "#version 120 void main(void) {    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); }"