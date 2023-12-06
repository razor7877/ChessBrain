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
		{ PieceType::PAWN, new Texture("images/w_pawn_png_1024px.png", true) },
		{ PieceType::BISHOP, new Texture("images/w_bishop_png_1024px.png", true) },
		{ PieceType::KING, new Texture("images/w_king_png_1024px.png", true) },
		{ PieceType::QUEEN, new Texture("images/w_queen_png_1024px.png", true) },
		{ PieceType::KNIGHT, new Texture("images/w_knight_png_1024px.png", true) },
		{ PieceType::ROOK, new Texture("images/w_rook_png_1024px.png", true) },
	};

	blackPieceTextures = {
		{ PieceType::PAWN, new Texture("images/b_pawn_png_1024px.png", true) },
		{ PieceType::BISHOP, new Texture("images/b_bishop_png_1024px.png", true) },
		{ PieceType::KING, new Texture("images/b_king_png_1024px.png", true) },
		{ PieceType::QUEEN, new Texture("images/b_queen_png_1024px.png", true) },
		{ PieceType::KNIGHT, new Texture("images/b_knight_png_1024px.png", true) },
		{ PieceType::ROOK, new Texture("images/b_rook_png_1024px.png", true) },
	};

	// Create the shader for the board
	this->boardShader = new Shader(
		"shaders/board.vert",
		"shaders/board.frag"
	);

	// Show no active case on the board at first
	this->boardShader->use().setVec2("activeCase", glm::vec2(-1.0f));

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
		"shaders/piece.vert",
		"shaders/piece.frag"
	);
}

Renderer::~Renderer()
{
	delete pieceShader;

	for (const auto & [piece, sprite] : this->pieceToSprite)
		delete sprite;

	for (const auto & [pieceType, texture] : this->whitePieceTextures)
		delete texture;

	for (const auto & [pieceType, texture] : this->blackPieceTextures)
		delete texture;
}

void Renderer::setupRenderer(Board* board)
{
	this->clearSprites();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Spot* spot = board->getSpot(x, y);
			if (spot->piece != nullptr)
			{
#ifdef DEBUG_MODE
				//std::cout << "Piece at " << x << " " << y << "\n";
#endif
				this->addPiece(spot->piece, x, y);
			}

		}
	}

	board->showBoardToConsole();
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

	this->pieceToSprite[piece] = pawnSprite;

	return pawnSprite;
}

void Renderer::movePiece(Piece* piece, uint8_t x, uint8_t y)
{
	this->pieceToSprite[piece]->moveSprite(x, y);
}

void Renderer::deletePiece(Piece* piece)
{
	delete this->pieceToSprite[piece];
	this->pieceToSprite.erase(piece);
}

void Renderer::clearSprites() { this->pieceToSprite.clear(); }

void Renderer::drawFrame()
{
	// Clear buffers before drawing next frame
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the board
	this->boardShader->use();
	glBindVertexArray(this->boardVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Draw all chess pieces sprites
	this->pieceShader->use();
	for (const auto & [piece, sprite] : this->pieceToSprite)
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

void Renderer::setActiveCase(glm::vec2 activeCase) { this->boardShader->use().setVec2("activeCase", activeCase); }