#include <stdlib.h>

#include "pieces/pawn.hpp"

Pawn::Pawn(bool white) : Piece::Piece(white){}

bool Pawn::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	if (abs(start->x - end->x) == 1)
	{
		if (end->piece == nullptr)
			return false;
	}
	// Can't move left/right
	else if (start->x != end->x)
		return false;

	// White pawn can only move forward
	if (this->isWhite())
	{
		int distY = end->y - start->y;
		// If not first move and not moving by one case forward
		// or first move but trying to move more than 2 forward
		if ((!firstMove && (distY) != 1) ||
			distY > 2)
			return false;

		// If jumping two spots, make sure first spot is empty
		if (distY == 2)
		{
			Spot* nextSpot = board->getSpot(start->x - 1, start->y);
			if (nextSpot->piece != nullptr)
				return false;
		}
	}
	// Black pawn can only move backward
	else
	{
		int distY = start->y - end->y;
		// If not first move and not moving by one case backward
		// or first move but trying to move more than 2 backward
		if ((!firstMove && distY != 1) ||
			distY > 2)
			return false;

		// If jumping two spots, make sure first spot is empty
		if (distY == 2)
		{
			Spot* nextSpot = board->getSpot(start->x - 1, start->y - 2);
			if (nextSpot->piece != nullptr)
				return false;
		}
	}

	this->firstMove = false;

	return true;
}

PieceType Pawn::getType() { return PieceType::PAWN; }
