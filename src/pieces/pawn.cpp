#include <stdlib.h>

#include "pieces/pawn.hpp"

Pawn::Pawn(bool white) : Piece::Piece(white){}

bool Pawn::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// Can't move left/right
	if (start->x != end->x)
		return false;

	// White pawn can only move forward
	if (this->isWhite())
	{
		// If not first move and not moving by one case forward
		// or first move but trying to move more than 2 forward
		if ((!firstMove && (end->y - start->y) != 1) ||
			(end->y - start->y) > 2)
			return false;
	}
	// Black pawn can only move backward
	else
	{
		// If not first move and not moving by one case backward
		// or first move but trying to move more than 2 backward
		if ((!firstMove && (start->y - end->y) != 1) ||
			(start->y - end->y) > 2)
			return false;
	}

	this->firstMove = false;

	return true;
}

PieceType Pawn::getType() { return PieceType::PAWN; }
