#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"

struct Sprite
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texCoordsBO;
	Texture* tex;
	glm::mat4 modelMatrix;
	~Sprite();
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawFrame();

private:
	// Vertices for a quad
	const static float quadVerts[];
	// Tex coords for drawing a texture to a quad
	const static float quadTexCoords[];
	std::vector<Sprite*> sprites;

	Shader* pieceShader;
};