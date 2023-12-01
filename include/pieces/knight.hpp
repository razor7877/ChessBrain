#pragma once
#include "piece.hpp"

class Knight : public virtual Piece
{
public:
	Knight(bool white);
	virtual bool canMove(Board* board, Spot* start, Spot* end);
	virtual PieceType getType();
};