#pragma once
#include "piece.hpp"

class Bishop : public virtual Piece
{
public:
	Bishop(bool white);
	virtual bool canMove(Board* board, Spot* start, Spot* end);
	virtual PieceType getType();
};