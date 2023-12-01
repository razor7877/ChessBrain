#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <graphics/stb_image.h>

#include "graphics/renderer.hpp"
#include "graphics/texture.hpp"
#include "graphics/shader.hpp"
#include "game/game.hpp"
#include "game/humanPlayer.hpp"

// Enable this for more verbose information on what is happening
#define DEBUG_MODE

constexpr float caseSize = 1.0f / 8.0f;

// Startup resolution
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Current resolution (can be changed by window resize callbacks)
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

GLFWwindow* window;

glm::vec2 activeCase = glm::vec2(0.0f);
bool caseUpdate = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Quit program when pressinc ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// If the user left clicked somewhere in the window
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		// Get the position of the click
		glfwGetCursorPos(window, &xpos, &ypos);

		// Get x,y position as a 0 to 1 ratio relative to screen size
		xpos /= windowWidth;
		// GLFW coordinates starts from the top left corner but we want to start from the bottom left
		// so we calculate 1 minus the ratio
		ypos = 1 - (ypos / windowHeight);
		int xCase = xpos / caseSize;
		int yCase = ypos / caseSize;

#ifdef DEBUG_MODE
		std::cout << "Click at x,y: " << xCase << "," << yCase << "\n";
#endif

		activeCase = glm::vec2(xCase, yCase);
		caseUpdate = true;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resized window\n";
	windowWidth = width;
	windowHeight = height;
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
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

	// Create the shader for the board
	Shader boardShader = Shader(
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.vert",
		"C:/Users/kylia/Desktop/GitHub/ChessBrain/src/shaders/board.frag"
	);

	// Creates a quad that is used to draw the board
	float vertices[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};
	
	// Board
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	HumanPlayer p1 = HumanPlayer(true);
	HumanPlayer p2 = HumanPlayer(false);
	Game game = Game(p1, p2);

	Renderer* renderer = new Renderer();
	game.setupRenderer(renderer);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear buffers before drawing next frame
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (caseUpdate)
		{
			caseUpdate = false;
			boardShader.setVec2("activeCase", activeCase);
		}
		
		renderer->drawFrame();

		// Swap new frame and poll GLFW for inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
    return 0;
}
