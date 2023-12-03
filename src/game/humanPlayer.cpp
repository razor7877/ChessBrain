#include <iostream>

#include "game/humanPlayer.hpp"


HumanPlayer::HumanPlayer(bool whiteSide)
{
	this->isNextMoveReady = false;
	this->whiteSide = whiteSide;
	this->humanPlayer = true;
}

bool HumanPlayer::getIsNextMoveReady() { return this->isNextMoveReady; }

glm::vec4 HumanPlayer::getNextInputs()
{
	return glm::vec4(1.0f);
}