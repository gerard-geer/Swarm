#version 400

smooth in vec2 texCoord;

out vec4 colorOut;

uniform sampler2D fboSamples;

const int sampleAmount = 50;

const float blurSize = (1.0/(float(sampleAmount)*51.2))*2;

void main()
{

	colorOut = vec4(0.0);

	for(int index = 0; index < sampleAmount; index++)
	{
		double i = double(index-(index/2));
		colorOut += texture2D(fboSamples, vec2(texCoord.x, texCoord.y - i*blurSize)) * 0.05;
	}
	colorOut = pow(colorOut, vec4(2));

}