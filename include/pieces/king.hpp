#pragma once
#include "piece.hpp"

class King : public virtual Piece
{
	virtual bool canMove(Board board, Spot start, Spot end);
};