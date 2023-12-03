#include "game/player.hpp"

Player::Player(bool isWhite)
{
	this->whiteSide = isWhite;
}

bool Player::isWhiteSide() { return this->whiteSide; }