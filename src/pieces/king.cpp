#include <stdlib.h>

#include "pieces/king.hpp"

King::King(bool white) : Piece::Piece(white){}

bool King::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// King can only move up to one spot in each axis
	int distX = abs(start->x - end->x);
	int distY = abs(start->y - end->y);
	if (distX > 1 || distY > 1)
		return false;

	return true;
}

PieceType King::getType() { return PieceType::KING; }