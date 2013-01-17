#version 400

/*
	The smooth (goreaud interpolated) vertex color is passed in from the vertex
	shader and into the fragment shader for use coloring the pixel.
*/
smooth in vec3 theColor;

/*
	In GLSL 1.5 and beyond (I think) we must specifiy a single output variable
	of a 4D vector type to pass out of the fragment shader. This vec4 becomes
	the color of the pixel.
*/
out vec4 outputColor;

/*
	We receive a float from CPU side to tell us the current amount of runtime
	the program has had.
	(uniform variables are variables that do not change over the course
	(of a frame.)
*/
uniform float time;

// This syntax should be simple.
void main()
{
	// Set the output color to be trigometrically modulated by the current time.
	outputColor = vec4(
	pow(theColor.r*sin(time), 2),
	pow(theColor.g*cos(time), 2),
	pow(theColor.b*sin(time+.25),2),
	1);

	// We add .01 to each channel so that every channel has a non zero value.
	// with additive blending enabled, this allows every possible output
	// from this shader to add up to white.
	outputColor += .01f;
}