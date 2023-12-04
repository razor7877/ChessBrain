#include <stdlib.h>
#include <iostream>

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

	// True if moving in the positive X direction, false if moving in negative direction
	bool isPositiveXDist = end->x - start->x > 0 ? true : false;
	// True if moving in the positive Y direction false if moving in negative direction
	bool isPositiveYDist = end->y - start->y > 0 ? true : false;

	int dirMoveX = isPositiveXDist ? 1 : -1;
	int dirMoveY = isPositiveYDist ? 1 : -1;

#ifdef DEBUG_MODE
	std::cout << "Moving bishop with dist: " << distX << "\n";
#endif

	// Check all spots along the distance moved to check for spots with pieces blocking the move
	for (int i = 1; i < distX; i++)
	{
		// Removing 1 from all coords to map from 1:8 to 0:7
		int x = start->x - 1 + dirMoveX * i;
		int y = start->y - 1 + dirMoveY * i;
		Spot* nextSpot = board->getSpot(x, y);

		if (nextSpot->piece != nullptr)
			return false;
	}

	return true;
}

PieceType Bishop::getType() { return PieceType::BISHOP; }