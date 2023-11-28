#pragma once
#include "piece.hpp"

class Queen : public virtual Piece
{
public:
	Queen(bool white);
	virtual bool canMove(Board board, Spot start, Spot end);
	virtual PieceType getType();
};