#pragma once
#include <glm/glm.hpp>

#include "game/player.hpp"

class HumanPlayer : public virtual Player
{
public:
	bool isNextMoveReady;

	HumanPlayer(bool whiteSide);
	virtual bool getIsNextMoveReady();
	virtual glm::vec4 getNextInputs();
};
