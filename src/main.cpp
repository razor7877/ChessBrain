#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "main.hpp"
#include "game/game.hpp"
#include "game/humanPlayer.hpp"

// Startup resolution
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Current resolution (can be changed by window resize callbacks)
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

GLFWwindow* window;

glm::vec2 activeCase = glm::vec2(-1.0f);

Renderer* renderer;
HumanPlayer* p1;
HumanPlayer* p2;
Game* game;

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

		glm::vec2 clickedCase = glm::vec2(xCase, yCase);
		updatePlayerInput(clickedCase);
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

void updatePlayerInput(glm::vec2 clickedCase)
{
#ifdef DEBUG_MODE
	std::cout << "Active case: " << activeCase.x << "," << activeCase.y << "\n";
#endif
	
	if (activeCase != glm::vec2(-1.0f))
	{
		// Clicking on same case, cancel selection
		if (clickedCase == activeCase)
		{
			renderer->setActiveCase(glm::vec2(-1.0f));
			activeCase = glm::vec2(-1.0f);
		}
		// If a case was clicked which isn't the same as the selected one, attempt move
		else if (game->playerMove(game->getCurrentPlayer(), activeCase.x, activeCase.y, clickedCase.x, clickedCase.y))
		{
			renderer->setActiveCase(glm::vec2(-1.0f));
			activeCase = glm::vec2(-1.0f);
		}
			
	}
	// Click on valid case, select it
	else if (game->isValidCaseClick(clickedCase))
	{
#ifdef DEBUG_MODE
		std::cout << "Selected case: " << clickedCase.x << "," << clickedCase.y << "\n";
#endif
		renderer->setActiveCase(clickedCase);
		activeCase = clickedCase;
	}
}

int main()
{
	if (setupGlfwContext() != 0)
	{
		return -1;
	}

	renderer = new Renderer();
	p1 = new HumanPlayer(true);
	p2 = new HumanPlayer(false);
	game = new Game(renderer, p1, p2);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		renderer->drawFrame();

		// Swap new frame and poll GLFW for inputs
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Free up heap
	delete renderer;
	delete p1;
	delete p2;
	delete game;

	glfwTerminate();
    return 0;
}
