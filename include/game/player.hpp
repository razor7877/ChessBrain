#pragma once

// An abstract class that represents a player
class Player
{
public:
	bool whiteSide;
	bool humanPlayer;

	bool isWhiteSide();
	bool isHumanPlayer();
};