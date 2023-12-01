#pragma once
#include "piece.hpp"

class Pawn : public virtual Piece
{
public:
	Pawn(bool white);
	virtual bool canMove(Board* board, Spot* start, Spot* end);
	virtual PieceType getType();

private:
	bool firstMove = true;
};