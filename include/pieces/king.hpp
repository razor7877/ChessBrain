#pragma once
#include "piece.hpp"

class King : public virtual Piece
{
public:
	King(bool white);
	virtual bool canMove(Board board, Spot start, Spot end);
	virtual PieceType getType();
};