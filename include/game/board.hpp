#pragma once
#include "game/spot.hpp"

class Spot;

// A class representing a board object, which contains an 8x8 matrix of spots for the chess pieces
class Board
{
public:
	Board();
	~Board();
	// Resets the board to it's starting state
	void resetBoard();
	void dumpBoardToConsole();
	void showBoardToConsole();
	// Helper function to match actual x,y coords to the corresponding spot in the array
	Spot getSpot(uint8_t x, uint8_t y);

private:
	// A two dimensional array containing the spots
	// It's a row major array, the first index selects the row, the second one select the column
	Spot** boxes;
};
