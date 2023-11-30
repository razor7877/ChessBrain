#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/stb_image.h>

#include "graphics/texture.hpp"
#include "graphics/shader.hpp"
#include "game/game.hpp"
#include "game/humanPlayer.hpp"
#include "game/player.hpp"

// Startup resolution
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Current resolution (can be changed by window resize callbacks)
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

GLFWwindow* window;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Quit program when pressinc ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resized window\n";
	glViewport(0, 0, width, height);
}

int setupGlfwContext()
{
	// Intialize GLFW context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ChessBrain", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Set callback functions for window resizing and handling input
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	
	// Check if GLAD loaded successfully
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

int main()
{
	if (setupGlfwContext() != 0)
	{
		return -1;
	}

	glEnable(GL_BLEND);

	// Creates a quad that is used to draw the board
	float vertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};

	// Create the shader for the board
	Shader boardShader = Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.frag"
	);

	Shader pieceShader = Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/piece.frag"
	);

	// Board
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// One pawn
	// Image from https://opengameart.org/content/chess-pieces-and-board-squares
	Texture pawn = Texture("C:/Users/kylia/Desktop/GitHub/ChessBrain/images/b_bishop_png_1024px.png");
	float pawnQuad[] = {
		-1.0f, 1.0f, 0.0f, // Top left
		1.0f, 1.0f, 0.0f, // Top right
		-1.0f, -1.0f, 0.0f, // Bottom left

		1.0f, 1.0f, 0.0f, // Top right
		1.0f, -1.0f, 0.0f, // Bottom right
		-1.0f, -1.0f, 0.0f, // Bottom left
	};
	float pawnTexCoords[] = {
		0.0f, 1.0f, // Top left
		1.0f, 1.0f, // Top right
		0.0f, 0.0f, // Bottom left

		1.0f, 1.0f, // Top right
		1.0f, 0.0f, // Bottom right
		0.0f, 0.0f, // Bottom left
	};

	unsigned int pawnVAO, pawnVBO, pawnTexCoordsBO;
	// Generate VAO and VBO and bind them
	glGenVertexArrays(1, &pawnVAO);
	glGenBuffers(1, &pawnVBO);

	glBindVertexArray(pawnVAO);

	// Send vertices
	glBindBuffer(GL_ARRAY_BUFFER, pawnVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Enable layout 0 input in shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Send tex coords
	glGenBuffers(1, &pawnTexCoordsBO);

	glBindBuffer(GL_ARRAY_BUFFER, pawnTexCoordsBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pawnTexCoords), pawnTexCoords, GL_STATIC_DRAW);

	// Enable layout 1 input in shader
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	float x = -7;
	float y = -5;
	glm::mat4 pawnModelMatrix = glm::mat4(1.0f);
	pawnModelMatrix = glm::scale(pawnModelMatrix, glm::vec3(1.0f / 8.0f));
	pawnModelMatrix = glm::translate(pawnModelMatrix, glm::vec3(x, y, 0.0f));

	pieceShader.use();
	pieceShader.setMat4("model", pawnModelMatrix);

	HumanPlayer p1 = HumanPlayer(true);
	HumanPlayer p2 = HumanPlayer(false);
	Game game = Game(p1, p2);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		boardShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		pieceShader.use();
		glBindVertexArray(pawnVAO);
		glBindTexture(GL_TEXTURE_2D, pawn.texID);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Swap new frame and poll GLFW for inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}
