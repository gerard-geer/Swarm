#version 400
/*
	This is another Composite FBO Shader. Notice again the names of the samplers.

	What this shader does is takes the framebuffer that the original Flies
	were rendered to, as well as the one that they were bloomed and abberated on,
	and combines them.

	Also it mirrors each texel across all four quadrants. It's not bad.
*/
smooth in vec2 texCoord;

/*
	This variable is entirely unnecessary.
*/
out vec4 colorOut;

/*
	The samplers bound to the render textures of the various FrameBuffers added to the
	Composite FBO Quad.
*/
uniform sampler2D fboSampler0;
uniform sampler2D fboSampler1;

/*
	HERP
*/
void main()
{
	// This first section takes a texel of the original render pass, and 
	// combines it with the corresponding pixel from the other 3 quadrants.
	vec4 prePostProcessed  = texture(fboSampler0, texCoord);
	prePostProcessed.a = .25f;

	vec4 prePostProcessedInvX = texture(fboSampler0, vec2(texCoord.x*-1+1, texCoord.y));
	prePostProcessedInvX.a = .25f;
	prePostProcessed+=prePostProcessedInvX;

	vec4 prePostProcessedInvY = texture(fboSampler0, vec2(texCoord.x, texCoord.y*-1+1));
	prePostProcessedInvY.a = .25f;
	prePostProcessed+=prePostProcessedInvY;

	vec4 prePostProcessedInvXY = texture(fboSampler0, vec2(texCoord*-1+1));
	prePostProcessedInvXY.a = .25f;
	prePostProcessed+=prePostProcessedInvXY;

	// Here we do the same with texels from the first post-processed pass.
	vec4 postProcessed = texture(fboSampler1, texCoord);
	postProcessed.a = .25f;

	vec4 postProcessedInvX = texture(fboSampler1, vec2(texCoord.x*-1+1, texCoord.y));
	postProcessedInvX.a = .25f;
	postProcessed+=postProcessedInvX;

	vec4 postProcessedInvY = texture(fboSampler1, vec2(texCoord.x, texCoord.y*-1+1));
	postProcessedInvY.a = .25f;
	postProcessed+=postProcessedInvY;

	vec4 postProcessedInvXY = texture(fboSampler1, vec2(texCoord*-1+1));
	postProcessedInvXY.a = .25f;
	postProcessed+=postProcessedInvXY;

	// Finally we combine them and spit them out.
	colorOut = prePostProcessed + postProcessed;
}

