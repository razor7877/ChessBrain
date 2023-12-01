#version 330 core

in vec3 position;

out vec4 FragColor;

uniform vec2 activeCase;

void main()
{
	// Define the checkerboard pattern
    int checkers = int(mod(position.x * 4.0, 2.0)) ^ int(mod(position.y * 4.0, 2.0));

	vec3 whiteColor = vec3(0.87);
	vec3 blackColor = vec3(0.2);

	vec3 color = mix(whiteColor, blackColor, float(checkers));
	FragColor = vec4(color, 1.0);
}