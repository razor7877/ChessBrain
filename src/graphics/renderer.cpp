#include "graphics/renderer.hpp"

const float Renderer::quadVerts[] = {
	-1.0f, 1.0f, 0.0f, // Top left
	1.0f, 1.0f, 0.0f, // Top right
	-1.0f, -1.0f, 0.0f, // Bottom left

	1.0f, 1.0f, 0.0f, // Top right
	1.0f, -1.0f, 0.0f, // Bottom right
	-1.0f, -1.0f, 0.0f, // Bottom left
};

const float Renderer::quadTexCoords[] = {
	0.0f, 1.0f, // Top left
	1.0f, 1.0f, // Top right
	0.0f, 0.0f, // Bottom left

	1.0f, 1.0f, // Top right
	1.0f, 0.0f, // Bottom right
	0.0f, 0.0f, // Bottom left
};

Renderer::Renderer()
{
	// Enable transparency
	glEnable(GL_BLEND);

	this->pieceShader = &Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);

	this->pieceShader->use();

	Sprite pawnSprite = Sprite();

	// One pawn
	// Image from https://opengameart.org/content/chess-pieces-and-board-squares
	Texture pawnTex = Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_bishop_png_1024px.png");
	pawnSprite.tex = &pawnTex;
	
	// Generate VAO and VBO and bind them
	glGenVertexArrays(1, &pawnSprite.VAO);
	glGenBuffers(1, &pawnSprite.VBO);

	glBindVertexArray(pawnSprite.VAO);

	// Send vertices
	glBindBuffer(GL_ARRAY_BUFFER, pawnSprite.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->quadVerts), this->quadVerts, GL_STATIC_DRAW);

	// Enable layout 0 input in shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Send tex coords
	glGenBuffers(1, &pawnSprite.texCoordsBO);

	glBindBuffer(GL_ARRAY_BUFFER, pawnSprite.texCoordsBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexCoords), this->quadTexCoords, GL_STATIC_DRAW);

	// Enable layout 1 input in shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	float realX = 0;
	float realY = 0;
	// Chess piece coords are x,y between 0-7
	// After scaling, when translating the piece, bottom left corner becomes -7,-7 (x,y)
	// and top right corner becomes 7,7 (x,y), thus, we need a way to get the correct translation
	float x = realX > 3 ? (7 - 2 * realX) : (-7 + 2 * realX);
	float y = realY > 3 ? (7 - 2 * realY) : (-7 + 2 * realY);
	pawnSprite.modelMatrix = glm::mat4(1.0f);
	pawnSprite.modelMatrix = glm::scale(pawnSprite.modelMatrix, glm::vec3(1.0f / 8.0f));
	// Translation is relative to previous scaling
	pawnSprite.modelMatrix = glm::translate(pawnSprite.modelMatrix, glm::vec3(x, y, 0.0f));

	pieceShader->use();
	pieceShader->setMat4("model", pawnSprite.modelMatrix);

	this->sprites.push_back(pawnSprite);
}

void Renderer::drawFrame()
{
	pieceShader->use();
	for (Sprite sprite : this->sprites)
	{
		glBindVertexArray(sprite.VAO);
		glBindTexture(GL_TEXTURE_2D, sprite.tex->texID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}