#pragma once
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

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
	Sprite* addPiece(Piece* piece, uint8_t x, uint8_t y);
	void drawFrame();

	Shader* boardShader;
	Shader* pieceShader;

private:
	unsigned int boardVAO;
	unsigned int boardVBO;
	std::vector<Sprite*> sprites;
	std::map<PieceType, Texture*> whitePieceTextures;
	std::map<PieceType, Texture*> blackPieceTextures;
};