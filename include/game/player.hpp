#pragma once
#include <glm/glm.hpp>

#include "game/game.hpp"

class Game;

// An abstract class that represents a player
class Player
{
public:
	bool whiteSide;
	bool isAiPlayer;

	Player(bool isWhite);
	virtual void playNextMove(Game* currentGame) = 0;
	bool isWhiteSide();
	bool isComputer();
};