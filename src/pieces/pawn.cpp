#include <stdlib.h>

#include "pieces/pawn.hpp"

Pawn::Pawn(bool white) : Piece::Piece(white){}

bool Pawn::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	int distX = abs(end->x - start->x);
	int distY = abs(end->y - start->y);

	// 1 case move on X axis might be diagonal attack
	if (distX == 1)
	{
		// It is only valid if end spot contains enemy piece and we're only moving one case on Y axis
		if (end->piece == nullptr || distY != 1)
			return false;
	}
	// Can't move left/right
	else if (start->x != end->x)
		return false;
	// This case means piece is moved forward (no x movement), make sure it is not landing on another piece
	else if (end->piece != nullptr)
		return false;

	// If not first move and not moving by one case backward
	// or first move but trying to move more than 2 backward
	if ((!firstMove && distY != 1) ||
		distY > 2)
		return false;

	// If black piece, offset y by -2 to check the spot under the piece
	// Otherwise, if white, no offset to check the spot above the piece
	int yOffset = this->isWhite() ? 0 : -2;

	// If jumping two spots, make sure first spot is empty
	if (distY == 2)
	{
		// Remove 1 from x to map from 1-8 to 0-7
		Spot* nextSpot = board->getSpot(start->x - 1, start->y + yOffset);
		if (nextSpot->piece != nullptr)
			return false;
	}

	this->firstMove = false;

	return true;
}

PieceType Pawn::getType() { return PieceType::PAWN; }
