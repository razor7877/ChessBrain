#pragma once
#include "piece.hpp"

class Knight : public virtual Piece
{
	virtual bool canMove(Board board, Spot start, Spot end);
};