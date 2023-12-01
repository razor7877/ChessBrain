#include <iostream>

#include "game/humanPlayer.hpp"


HumanPlayer::HumanPlayer(bool whiteSide)
{
	this->whiteSide = whiteSide;
	this->humanPlayer = true;
	this->currentCase = glm::vec2(0.0f);
}