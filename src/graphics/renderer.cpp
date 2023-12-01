#include "graphics/renderer.hpp"
#include <iostream>

Renderer::Renderer()
{
	// Enable transparency
	glEnable(GL_BLEND);

	this->pieceShader = new Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);

	Sprite* pawnSprite = new Sprite();

	// One pawn
	// Image from https://opengameart.org/content/chess-pieces-and-board-squares
	Texture* pawnTex = new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_bishop_png_1024px.png");
	pawnSprite->tex = pawnTex;

	float realX = 0;
	float realY = 0;
	// Chess piece coords are x,y between 0-7
	// After scaling, when translating the piece, bottom left corner becomes -7,-7 (x,y)
	// and top right corner becomes 7,7 (x,y), thus, we need a way to get the correct translation
	float x = realX > 3 ? (7 - 2 * realX) : (-7 + 2 * realX);
	float y = realY > 3 ? (7 - 2 * realY) : (-7 + 2 * realY);
	pawnSprite->modelMatrix = glm::mat4(1.0f);
	pawnSprite->modelMatrix = glm::scale(pawnSprite->modelMatrix, glm::vec3(1.0f / 8.0f));
	// Translation is relative to previous scaling
	pawnSprite->modelMatrix = glm::translate(pawnSprite->modelMatrix, glm::vec3(x, y, 0.0f));

	this->pieceShader->use();
	this->pieceShader->setMat4("model", pawnSprite->modelMatrix);

	this->sprites.push_back(pawnSprite);
}

Renderer::~Renderer()
{
	delete pieceShader;

	for (Sprite* sprite : this->sprites)
		delete sprite;
}

void Renderer::drawFrame()
{
	this->pieceShader->use();
	//std::cout << "Shader ID: " << this->pieceShader->ID << "\n";
	for (Sprite* sprite : this->sprites)
	{
		glBindVertexArray(sprite->VAO);
		glBindTexture(GL_TEXTURE_2D, sprite->tex->texID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		std::cout << "Error code: " << glGetError() << "\n";
	}
}