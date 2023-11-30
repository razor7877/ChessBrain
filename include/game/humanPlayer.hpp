#pragma once
#include "game/player.hpp"
#include "game/move.hpp"

class HumanPlayer : public virtual Player
{
public:
	HumanPlayer(bool whiteSide);
};
