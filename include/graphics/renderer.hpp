#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/sprite.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawFrame();

private:
	std::vector<Sprite*> sprites;

	Shader* pieceShader;
};