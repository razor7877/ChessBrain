#pragma once
#include <glm/glm.hpp>

#include "game/player.hpp"
#include "game/move.hpp"

class HumanPlayer : public virtual Player
{
public:
	HumanPlayer(bool whiteSide);
};
