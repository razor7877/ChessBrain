#include <stdlib.h>

#include "pieces/queen.hpp"

Queen::Queen(bool white) : Piece::Piece(white){}

bool Queen::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// The queen can only move either diagonally, or in a line
	// First check if the movement is not in a line
	int distX = abs(start->x - end->x);
	int distY = abs(start->y - end->y);
	if ( (start->x != end->x && start->y != end->y) &&
		(distX != distY))
		return false;

	return true;
}

PieceType Queen::getType() { return PieceType::QUEEN; }