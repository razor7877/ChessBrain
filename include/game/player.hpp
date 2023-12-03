#pragma once
#include <glm/glm.hpp>

// An abstract class that represents a player
class Player
{
public:
	bool whiteSide;
	bool humanPlayer;

	bool isWhiteSide();
	bool isHumanPlayer();
	virtual bool getIsNextMoveReady() = 0;
	virtual glm::vec4 getNextInputs() = 0;
};