#pragma once
#include "piece.hpp"

class Pawn : public virtual Piece
{
	virtual bool canMove(Board board, Spot start, Spot end);
};