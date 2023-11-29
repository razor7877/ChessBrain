#ifndef BOARD_HPP
#define BOARD_HPP
#include "game/spot.hpp"

class Spot;

// A class representing a board object, which contains an 8x8 matrix of spots for the chess pieces
class Board
{
public:
	// A two dimensional array containing the spots
	// It's a row major array, the first index selects the row, the second one select the column
	Spot** boxes;

	Board();
	~Board();
	// Resets the board to it's starting state
	void resetBoard();
	void dumpBoardToConsole();
	Spot getSpot(int x, int y);
};
#endif