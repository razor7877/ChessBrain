#version 330 core

in vec3 position;

out vec4 FragColor;

uniform vec2 activeCase;

void main()
{
	// To match the 0-7 x,y coords of the chess board, we want position with a range 0:1
	// instead of -1:1
	vec3 normalizedPos = (position + 1.0) / 2.0;
	// We get x,y coords through the uniform in range 0-7 but want a 0:1 range
	vec2 caseStart = activeCase * 0.125;
	vec2 caseEnd = (activeCase + 1.) * 0.125;
	// Draw selected case with different color
	if (normalizedPos.x > caseStart.x && normalizedPos.y > caseStart.y &&
		normalizedPos.x < caseEnd.x && normalizedPos.y < caseEnd.y)
	{
		FragColor = vec4(0.0, 0.8, 0.0, 1.0);
		return;
	}

	// Define the checkerboard pattern
    int checkers = int(mod(position.x * 4.0, 2.0)) ^ int(mod(position.y * 4.0, 2.0));

	vec3 whiteColor = vec3(0.87);
	vec3 blackColor = vec3(0.2);

	vec3 color = mix(whiteColor, blackColor, float(checkers));
	FragColor = vec4(color, 1.0);
}