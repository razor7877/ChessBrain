#ifdef DEBUG_MODE
#include <iostream>
#endif

#include "graphics/renderer.hpp"

Renderer::Renderer()
{
	// Enable transparency
	glEnable(GL_BLEND);

	this->pieceShader = new Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);

	this->pieceShader->use();

	// Images from https://opengameart.org/content/chess-pieces-and-board-squares
	whitePieceTextures = {
		{ PieceType::PAWN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_pawn_png_1024px.png", true) },
		{ PieceType::BISHOP, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_bishop_png_1024px.png", true) },
		{ PieceType::KING, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_king_png_1024px.png", true) },
		{ PieceType::QUEEN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_queen_png_1024px.png", true) },
		{ PieceType::KNIGHT, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_knight_png_1024px.png", true) },
		{ PieceType::ROOK, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/w_rook_png_1024px.png", true) },
	};

	blackPieceTextures = {
		{ PieceType::PAWN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_pawn_png_1024px.png", true) },
		{ PieceType::BISHOP, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_bishop_png_1024px.png", true) },
		{ PieceType::KING, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_king_png_1024px.png", true) },
		{ PieceType::QUEEN, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_queen_png_1024px.png", true) },
		{ PieceType::KNIGHT, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_knight_png_1024px.png", true) },
		{ PieceType::ROOK, new Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_rook_png_1024px.png", true) },
	};
}

Renderer::~Renderer()
{
	delete pieceShader;

	for (Sprite* sprite : this->sprites)
		delete sprite;

	for (const auto& pair : this->whitePieceTextures)
		delete pair.second;

	for (const auto& pair : this->blackPieceTextures)
		delete pair.second;
}

Sprite* Renderer::addPiece(Piece* piece, uint8_t x, uint8_t y)
{
	Texture* pieceTexture;
	if (piece->isWhite())
		pieceTexture = this->whitePieceTextures.at(piece->getType());
	else
		pieceTexture = this->blackPieceTextures.at(piece->getType());

	Sprite* pawnSprite = new Sprite(pieceTexture);

	// Chess piece coords are x,y between 0-7
	// After scaling, when translating the piece, bottom left corner becomes -7,-7 (x,y)
	// and top right corner becomes 7,7 (x,y), thus, we need a way to get the correct translation
	float mappedX = -7 + 2 * x;
	float mappedY = -7 + 2 * y;

	// Translation is relative to previous scaling
	pawnSprite->modelMatrix = glm::translate(pawnSprite->modelMatrix, glm::vec3(mappedX, mappedY, 0.0f));

#ifdef DEBUG_MODE
	std::cout << "Sprite: " << pawnSprite << "mapped at: " << mappedX << "," << mappedY << "\n";
#endif
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
		this->pieceShader->setMat4("model", sprite->modelMatrix);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

#ifdef DEBUG_MODE
	// Check for any potential OpenGL errors and print them
	unsigned int errorCode = glGetError();
	if (errorCode != 0)
		std::cout << "OpenGL error code: " << errorCode << "\n";
#endif
}