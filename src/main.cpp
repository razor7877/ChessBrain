#include <iostream>

#include "main.hpp"
#include "game/game.hpp"
#include "game/humanPlayer.hpp"

#include "tsl/platform/ml_dtypes.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "tensorflow/cc/saved_model/tag_constants.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/public/session_options.h"
#include "tensorflow/core/framework/logging.h"

// Startup resolution
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

// Current resolution (can be changed by window resize callbacks)
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;// Current resolution (can be changed by window resize callbacks)

GLFWwindow* window;

Renderer* renderer;
HumanPlayer* p1;
HumanPlayer* p2;
Game* game;


int main()
{
	// We need to use SaveModelBundleLite as a in-memory model object for tensorflow's model bundle.
	const auto savedModelBundle = std::make_unique<tensorflow::SavedModelBundleLite>();

	// Create dummy options.
	tensorflow::SessionOptions sessionOptions;
	tensorflow::RunOptions runOptions;

	// Load the model bundle.
	const auto loadResult = tensorflow::LoadSavedModel(
		sessionOptions,
		runOptions,
		"models/model.pb", //std::string containing path of the model bundle
		{ tensorflow::kSavedModelTagServe },
		savedModelBundle.get());

	// Check if loading was okay.
	TF_CHECK_OK(loadResult);

	// Provide input data.
	tensorflow::Tensor tensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({ 2 }));
	tensor.vec<float>()(0) = 20.f;
	tensor.vec<float>()(1) = 6000.f;

	// Link the data with some tags so tensorflow know where to put those data entries.
	std::vector<std::pair<std::string, tensorflow::Tensor>> feedInputs = { {"serving_default_flatten_input:0", tensor} };
	std::vector<std::string> fetches = { "StatefulPartitionedCall:0" };

	// We need to store the results somewhere.
	std::vector<tensorflow::Tensor> outputs;

	// Let's run the model...
	auto status = savedModelBundle->GetSession()->Run(feedInputs, fetches, {}, &outputs);
	TF_CHECK_OK(status);

	// ... and print out it's predictions.
	for (const auto& record : outputs)
	{
		LOG(INFO) << record.DebugString();
	}

	if (setupGlfwContext() != 0)
	{
		return -1;
	}

	renderer = new Renderer();
	p1 = new HumanPlayer(true, renderer);
	p2 = new HumanPlayer(false, renderer);
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
		if (game->getCurrentPlayer() == p1)
			p1->updateInput(game, clickedCase);
		else
			p2->updateInput(game, clickedCase);
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
