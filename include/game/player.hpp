#pragma once

class Player
{
public:
	bool whiteSide;
	bool humanPlayer;

	bool isWhiteSide() { return this->whiteSide; }
	bool isHumanPlayer() { return this->humanPlayer; }
};