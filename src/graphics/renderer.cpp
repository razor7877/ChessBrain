#include "graphics/renderer.hpp"

#ifdef DEBUG_MODE
#include <iostream>
#endif

Renderer::Renderer()
{
	// Enable transparency
	glEnable(GL_BLEND);

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

	// Create the shader for the board
	this->boardShader = new Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.frag"
	);

	// Creates the board
	glGenVertexArrays(1, &boardVAO);
	glGenBuffers(1, &boardVBO);

	glBindVertexArray(boardVAO);
	glBindBuffer(GL_ARRAY_BUFFER, boardVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite::quadVerts), Sprite::quadVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Create the shader for drawing pieces
	this->pieceShader = new Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);
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
	pawnSprite->moveSprite(x, y);

	this->sprites.push_back(pawnSprite);

	return pawnSprite;
}

void Renderer::clearSprites() { this->sprites.clear(); }

void Renderer::drawFrame()
{
	// Draw the board
	this->boardShader->use();
	glBindVertexArray(this->boardVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Draw all chess pieces sprites
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