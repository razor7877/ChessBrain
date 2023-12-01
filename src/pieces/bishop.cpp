#include <stdlib.h>

#include "pieces/bishop.hpp"

Bishop::Bishop(bool white) : Piece::Piece(white){}

bool Bishop::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// The bishop can only move diagonally, this means that x and y movement must be equal
	int distX = abs(start->x - end->x);
	int distY = abs(start->y - end->y);
	if (distX != distY)
		return false;

	return true;
}

PieceType Bishop::getType() { return PieceType::BISHOP; }