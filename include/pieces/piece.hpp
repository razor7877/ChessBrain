#pragma once
#include "spot.hpp"
#include "board.hpp"

// Represents a single chess piece
class Piece
{
public:
	Piece(bool white);
	bool isWhite();
	void setWhite(bool white);
	bool isKilled();
	void setKilled(bool killed);

	virtual bool canMove(Board board, Spot start, Spot end) = 0;

private:
	bool killed = false;
	bool white = false;
};