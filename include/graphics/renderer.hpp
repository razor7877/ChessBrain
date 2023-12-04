#pragma once
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "main.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/sprite.hpp"
#include "pieces/piece.hpp"

// TODO : Use same quad VBO for all sprites, only change model matrix
class Renderer
{
public:
	Renderer();
	~Renderer();

	/// <summary>
	/// Iterates over the different pieces in the board, and sends all relevant information for the renderer to draw them to screen
	/// </summary>
	/// <param name="board">The board that the renderer should draw to the screen</param>
	void setupRenderer(Board* board);
	Sprite* addPiece(Piece* piece, uint8_t x, uint8_t y);
	void movePiece(Piece* piece, uint8_t x, uint8_t y);
	void deletePiece(Piece* piece);
	void clearSprites();
	void drawFrame();
	void setActiveCase(glm::vec2 activeCase);

private:
	unsigned int boardVAO;
	unsigned int boardVBO;
	// The renderer keeps a lookup table of a piece and it's associated sprite so that the game can update
	// movement of individual sprites with the movePiece method
	std::map<Piece*, Sprite*> pieceToSprite;
	std::map<PieceType, Texture*> whitePieceTextures;
	std::map<PieceType, Texture*> blackPieceTextures;

	Shader* boardShader;
	Shader* pieceShader;
};