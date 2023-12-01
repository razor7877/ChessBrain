#pragma once

#include <glm/glm.hpp>

#include "graphics/texture.hpp"

struct Sprite
{
	// Vertices for a quad
	const static float quadVerts[18];
	// Tex coords for drawing a texture to a quad
	const static float quadTexCoords[12];
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texCoordsBO;
	Texture* texture;
	glm::mat4 modelMatrix;
	Sprite(Texture* texture);
	void moveSprite(uint8_t x, uint8_t y);
};