#include <stdlib.h>
#include <iostream>

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

	bool isDiagonalMove = (distX == distY) ? true : false;

	// If moving diagonally, same path checking as for bishop (reusing same code)
	if (isDiagonalMove)
	{
		// True if moving in the positive X direction, false if moving in negative direction
		bool isPositiveXDist = end->x - start->x > 0 ? true : false;
		// True if moving in the positive Y direction false if moving in negative direction
		bool isPositiveYDist = end->y - start->y > 0 ? true : false;

		int dirMoveX = isPositiveXDist ? 1 : -1;
		int dirMoveY = isPositiveYDist ? 1 : -1;

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
#ifdef DEBUG_MODE
		std::cout << "Moving queen diagonally with dist: " << distX << "\n";
#endif
	}
	// If moving in a line, same path checking as for rook (reusing same comde)
	else
	{
		// True if moving on the x axis, false if moving on the y axis
		bool isXMove = start->x != end->x;
		// Gets the distance moved to know how many spots to check
		int distMoved = isXMove ? end->x - start->x : end->y - start->y;
		int dirMove = distMoved > 0 ? 1 : -1;
		distMoved = abs(distMoved);

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
#ifdef DEBUG_MODE
		std::cout << "Moving queen in a line with dist: " << distMoved << "\n";
#endif
	}

	return true;
}

PieceType Queen::getType() { return PieceType::QUEEN; }