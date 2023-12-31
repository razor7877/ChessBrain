#include "glad/glad.h"

#include <glm/ext/matrix_transform.hpp>

#include "main.hpp"
#include "graphics/sprite.hpp"

const float Sprite::quadVerts[] = {
	-1.0f, 1.0f, 0.0f, // Top left
	1.0f, 1.0f, 0.0f, // Top right
	-1.0f, -1.0f, 0.0f, // Bottom left

	1.0f, 1.0f, 0.0f, // Top right
	1.0f, -1.0f, 0.0f, // Bottom right
	-1.0f, -1.0f, 0.0f, // Bottom left
};

const float Sprite::quadTexCoords[] = {
	0.0f, 1.0f, // Top left
	1.0f, 1.0f, // Top right
	0.0f, 0.0f, // Bottom left

	1.0f, 1.0f, // Top right
	1.0f, 0.0f, // Bottom right
	0.0f, 0.0f, // Bottom left
};

Sprite::Sprite(Texture* texture)
{
	// Generate VAO and VBO and bind them
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	// Send vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->quadVerts), this->quadVerts, GL_STATIC_DRAW);

	// Enable layout 0 input in shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Send tex coords
	glGenBuffers(1, &this->texCoordsBO);

	glBindBuffer(GL_ARRAY_BUFFER, this->texCoordsBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexCoords), this->quadTexCoords, GL_STATIC_DRAW);

	// Enable layout 1 input in shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(caseSize));
	this->texture = texture;
}

void Sprite::moveSprite(uint8_t x, uint8_t y)
{
	// Chess piece coords are x,y between 0-7
	// After scaling, when translating the piece, bottom left corner becomes -7,-7 (x,y)
	// and top right corner becomes 7,7 (x,y), thus, we need a way to get the correct translation
	float mappedX = -7 + 2 * x;
	float mappedY = -7 + 2 * y;

	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::scale(this->modelMatrix, glm::vec3(caseSize));
	// Translation is relative to previous scaling
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(mappedX, mappedY, 0.0f));
}