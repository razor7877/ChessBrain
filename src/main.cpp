#include <iostream>

#include "main.hpp"
#include "game/game.hpp"
#include "game/humanPlayer.hpp"
#include "game/aiPlayer.hpp"

#define H_V_H 0
#define H_V_AI 1
#define AI_V_AI 2
// Use this define to set up a human player against AI
// Otherwise, game is set up with 2 human players
#define GAME_MODE 0

// Startup resolution
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Current resolution (can be changed by window resize callbacks)
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;

GLFWwindow* window;

Renderer* renderer; 
#if GAME_MODE == H_V_H || GAME_MODE == H_V_AI
HumanPlayer* p1;
#else
AiPlayer* p1;
#endif

#if GAME_MODE == H_V_H
HumanPlayer* p2;
#else
AiPlayer* p2;
#endif

Game* game;

int main()
{
	if (setupGlfwContext() != 0)
	{
		return -1;
	}

	renderer = new Renderer();

#if GAME_MODE == H_V_H || GAME_MODE == H_V_AI
	p1 = new HumanPlayer(true, renderer);
#else
	p1 = new AiPlayer(true);
#endif
#if GAME_MODE == H_V_H
	p2 = new HumanPlayer(false, renderer);
#else
	p2 = new AiPlayer(false, "http://localhost:10002/predict");
#endif

	game = new Game(renderer, p1, p2);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		game->playAnyQueuedMove();
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
#if GAME_MODE == H_V_H || GAME_MODE == H_V_AI
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
		if (game->getCurrentPlayer() == p1 && !p1->isComputer())
			p1->updateInput(game, clickedCase);
#if GAME_MODE == H_V_H
		else if (!p2->isComputer())
			p2->updateInput(game, clickedCase);
#endif
	}
#else
	std::cout << "Click occurred but game is running in AI vs AI mode\n";
#endif
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
