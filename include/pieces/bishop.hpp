#pragma once
#include "piece.hpp"

class Bishop : public virtual Piece
{
	virtual bool canMove(Board board, Spot start, Spot end);
};