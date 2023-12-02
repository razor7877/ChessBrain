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

	// True if moving on the x axis, false if moving on the y axis
	bool isXMove = start->x != end->x;
	// Gets the distance moved to know how many spots to check
	int distMoved = isXMove ? end->x - start->x : end->y - start->y;
	int dirMove = distMoved > 0 ? 1 : -1;
	distMoved = abs(distMoved);
	
#ifdef DEBUG_MODE
	std::cout << "Moving rook with dist: " << distMoved << "\n";
#endif
	// Check all spots along the moved axis to check for spots with pieces blocking the move
	for (int i = 1; i < distMoved; i++)
	{
		Spot* nextSpot;

		// Removing 1 from all coords to map from 1:8 to 0:7
		if (isXMove)
		{
			int x = start->x - 1 + i * dirMove;
			int y = start->y - 1;
			nextSpot = board->getSpot(x, y);
		}
		else
		{
			int x = start->x - 1;
			int y = start->y - 1 + i * dirMove;
			nextSpot = board->getSpot(x, y);
		}

		if (nextSpot->piece != nullptr)
			return false;
	}

	return true;
}

PieceType Rook::getType() { return PieceType::ROOK; }