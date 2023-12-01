#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "shader.hpp"
#include "texture.hpp"

struct Sprite
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int texCoordsBO;
	Texture* tex;
	glm::mat4 modelMatrix;
};

class Renderer
{
public:
	Renderer();
	void drawFrame();


	// Vertices for a quad
	const static float quadVerts[];
	// Tex coords for drawing a texture to a quad
	const static float quadTexCoords[];
	std::vector<Sprite> sprites;

	Shader* boardShader;
	Shader* pieceShader;
};