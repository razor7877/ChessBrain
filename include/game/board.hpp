#ifndef BOARD_HPP
#define BOARD_HPP
#include "game/spot.hpp"

class Spot;

class Board
{
public:
	Spot** boxes;
	Board();
	~Board();
	void resetBoard();
};
#endif