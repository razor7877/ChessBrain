#ifndef PIECE_HPP
#define PIECE_HPP
#include "game/board.hpp"
#include "game/spot.hpp"

class Board;
class Spot;

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
#endif