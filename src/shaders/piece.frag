#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
	// Discard fragment if texture is transparent at these coords
	if (texColor.a < 0.1)
		discard;
	FragColor = texColor;
}