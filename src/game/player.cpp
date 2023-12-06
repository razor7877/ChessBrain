#include "game/player.hpp"

Player::Player(bool isWhite)
{
	this->isAiPlayer = true;
	this->whiteSide = isWhite;
}

bool Player::isWhiteSide() { return this->whiteSide; }
bool Player::isComputer() { return this->isAiPlayer; }