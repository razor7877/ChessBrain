#include <stdlib.h>
#include <iostream>

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

	bool isXMove = start->x != end->x;
	int distMoved = isXMove ? abs(start->x - end->x) : abs(start->y - end->y);
	/*
#ifdef DEBUG_MODE
	std::cout << "Moving rook with dist: " << distMoved << "\n";
	for (int i = 0; i < distMoved; i++)
	{
		std::cout
	}
	
#endif*/

	return true;
}

PieceType Rook::getType() { return PieceType::ROOK; }