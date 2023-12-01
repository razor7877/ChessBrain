#include <stdlib.h>

#include "pieces/pawn.hpp"

Pawn::Pawn(bool white) : Piece::Piece(white){}

bool Pawn::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// If not moving by one case forward
	if (abs(start->y - end->y) != 1)
		return false;

	return true;
}

PieceType Pawn::getType() { return PieceType::PAWN; }
