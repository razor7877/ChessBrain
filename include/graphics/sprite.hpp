#pragma once

#include <glm/glm.hpp>

#include "graphics/texture.hpp"

struct Sprite
{
	// Vertices for a quad
	const static float quadVerts[];
	// Tex coords for drawing a texture to a quad
	const static float quadTexCoords[];
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texCoordsBO;
	Texture* tex;
	glm::mat4 modelMatrix;
	Sprite();
	~Sprite();
};