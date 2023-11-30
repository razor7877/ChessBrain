#include <iostream>

#include "game/humanPlayer.hpp"


HumanPlayer::HumanPlayer(bool whiteSide)
{
	this->whiteSide = whiteSide;
	this->humanPlayer = true;
}