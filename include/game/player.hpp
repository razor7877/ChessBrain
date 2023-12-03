#pragma once
#include <glm/glm.hpp>

// An abstract class that represents a player
class Player
{
public:
	bool whiteSide;

	Player(bool isWhite);
	bool isWhiteSide();
};