#version 400
/*
	It is important to note that this shader shades a polygon with the contents
	of a framebuffer. This is where some serious magic happens.
*/

/*
	This is the interpolated texture coordinate received from the vertex shader.
	It's a 2D vector--U, and V.
*/
smooth in vec2 texCoord;

/*
	GLSL 4.0 requires an output variable to read the final pixel color from.
	This is done to simplify rendering to multiple render targets.
*/
out vec4 colorOut;

/*
	This is a sampler that contains the texture data of the afore mentioned
	framebuffer.
*/
uniform sampler2D fboSamples;

/*
	We stretch the 3 color channels by different amounts so that at the edges
	of the screen the particle's bloom becomes chromatically abberated.
*/
vec4 performChromaticAbberation(vec4 originalTexel)
{

	// Create a vector that stores the amount we stretch the channels by.
	vec2 distortion = texCoord-vec2(.5, .5);

	// Make that amount tiny.
	distortion/=45;

	// Now we stretch each channel in a different direction.
	vec2 texCoordDistortedX = vec2(texCoord.x+distortion.x, texCoord.y);
	vec2 texCoordDistortedY = vec2(texCoord.x, texCoord.y+distortion.y);
	vec2 texCoordDistortedXY = vec2(texCoord.x+distortion.y, texCoord.y+distortion.y);

	// We take the distance from the center of the texel that we are working on
	// so that we can tone down the abberation as we work towards the center of the screen.
	float distFromCenter = abs( distance( texCoord, vec2(.5, .5) ) );

	// Create a fully abberated texel.
	vec4 aberratedTexel;
	aberratedTexel.r = texture(fboSamples, texCoordDistortedXY);
	aberratedTexel.g = texture(fboSamples, texCoordDistortedX);
	aberratedTexel.b = texture(fboSamples, texCoordDistortedY);
	aberratedTexel.a = 1.0f;

	// Now we use the distance from center to interpolate the normal and abberated texels.
	return (originalTexel * (1-distFromCenter)) + (aberratedTexel * (distFromCenter) );
}

void main()
{
	// Sample the sampler.
	colorOut = texture(fboSamples, texCoord);

	// Add abberation.
	colorOut+=performChromaticAbberation(colorOut);
}

