#include <stdlib.h>

#include "pieces/rook.hpp"

Rook::Rook(bool white) : Piece::Piece(white){}

bool Rook::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// Rook can only move on one axis at a time, so one of the coordinates must remain the same for move to be valid
	if (start->x != end->x && start->y != end->y)
		return false;

	return true;
}

PieceType Rook::getType() { return PieceType::ROOK; }