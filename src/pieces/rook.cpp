#include <stdlib.h>

#include "pieces/rook.hpp"

Rook::Rook(bool white) : Piece::Piece(white){}

bool Rook::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	if (start->x != end->x && start->y != end->y)
		return false;

	return true;
}

PieceType Rook::getType() { return PieceType::ROOK; }