#pragma once
#include "piece.hpp"

class Rook : public virtual Piece
{
	virtual bool canMove(Board board, Spot start, Spot end);
};