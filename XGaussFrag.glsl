#version 400
/*
	This is another shader that uses the texture of a framebuffer.
	What this does is takes the contents of a framebuffer, and renders it into another
	framebuffer blurred horizontally, convoluting each line.
*/
smooth in vec2 texCoord;

/*
	The standard color out.
*/
out vec4 colorOut;

/*
	The sampler that's bound to the previous pass' framebuffer.
*/
uniform sampler2D fboSamples;

/*
	How many samples of blur per texel do we want?
*/
const int sampleAmount = 50;

/*
	The convolution kernel size.
*/
const float blurSize = (1.0/(float(sampleAmount)*51.2))*2;

/*
	The main method.
*/
void main()
{
	
	// Declare an empty output vector so that we can add to it.
	colorOut = vec4(0.0);

	// Average the neighbors of each texel. Note that we do have negative indexing.
	// When using textureMode CLAMP_TO_EDGE, out-of-bounds samples return 0. This
	// has the side effect of vignetting the blur.
	for(int index = 0; index < sampleAmount; index++)
	{
		double i = double(index-(index/2));
		colorOut += texture2D(fboSamples, vec2(texCoord.x - i*blurSize, texCoord.y)) * .05;
	}

}