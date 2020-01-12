#verion 330
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;
uniform float sample;
uniform float sampleCount;
uniform float textureWidth;

void main()
{
	FragColor = texture(tex, vec2(TexCoord.x/sampleCount + (sample-1)/sampleCount, TexCoord.y));
}