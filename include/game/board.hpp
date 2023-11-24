#pragma once
#include "game/spot.hpp"

struct Board
{
	Spot boxes[8][8]{};
	Board();
	void resetBoard();
};