#pragma once
#include "piece.hpp"

class Rook : public virtual Piece
{
public:
	Rook(bool white);
	virtual bool canMove(Board board, Spot start, Spot end);
};