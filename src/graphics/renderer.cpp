#include "graphics/renderer.hpp"
#include <iostream>
#include <pieces/pawn.hpp>

Renderer::Renderer()
{
	// Enable transparency
	glEnable(GL_BLEND);

	this->pieceShader = new Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);

	// Images from https://opengameart.org/content/chess-pieces-and-board-squares
	pieceTextures = {
		{ PieceType::PAWN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_pawn_png_1024px.png") },
		{ PieceType::BISHOP, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_bishop_png_1024px.png") },
		{ PieceType::KING, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_king_png_1024px.png") },
		{ PieceType::QUEEN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_queen_png_1024px.png") },
		{ PieceType::KNIGHT, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_knight_png_1024px.png") },
		{ PieceType::ROOK, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_rook_png_1024px.png") },
	};

	Pawn* pawn = new Pawn(true);
	this->addPiece(pawn, 1, 1);
}

Renderer::~Renderer()
{
	delete pieceShader;

	for (Sprite* sprite : this->sprites)
		delete sprite;

	for (const auto& pair : this->pieceTextures)
		delete pair.second;
}

Sprite* Renderer::addPiece(Piece* piece, uint8_t x, uint8_t y)
{
	Sprite* pawnSprite = new Sprite(this->pieceTextures.at(piece->getType()));

	// Chess piece coords are x,y between 0-7
	// After scaling, when translating the piece, bottom left corner becomes -7,-7 (x,y)
	// and top right corner becomes 7,7 (x,y), thus, we need a way to get the correct translation
	float mappedX = x > 3 ? (7 - 2 * x) : (-7 + 2 * x);
	float mappedY = y > 3 ? (7 - 2 * y) : (-7 + 2 * y);

	// Translation is relative to previous scaling
	pawnSprite->modelMatrix = glm::translate(pawnSprite->modelMatrix, glm::vec3(mappedX, mappedY, 0.0f));

	std::cout << pawnSprite << "\n";
	this->sprites.push_back(pawnSprite);

	return pawnSprite;
}

void Renderer::drawFrame()
{
	this->pieceShader->use();

	for (Sprite* sprite : this->sprites)
	{
		glBindVertexArray(sprite->VAO);
		glBindTexture(GL_TEXTURE_2D, sprite->texture->texID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	// Check for any potential OpenGL errors and print them
	unsigned int errorCode = glGetError();
	if (errorCode != 0)
		std::cout << "OpenGL error code: " << errorCode << "\n";
}