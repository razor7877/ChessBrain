#include <stdlib.h>

#include "pieces/knight.hpp"

Knight::Knight(bool white) : Piece::Piece(white){}

bool Knight::canMove(Board* board, Spot* start, Spot* end)
{
	// Can't go over piece of same color
	if (end->piece != nullptr && end->piece->isWhite() == this->isWhite())
		return false;

	// The knight can move either 2 spots on the x axis and 1 on the y axis or the opposite (1 on x, 2 on y)
	// sum of x + y movement must then be equal to 3, but neither x or y should be larger than 2
	int distX = abs(start->x - end->x);
	int distY = abs(start->y - end->y);

	if (distX > 2 || distY > 2 || (distX + distY) != 3)
		return false;

	return true;
}

PieceType Knight::getType() { return PieceType::KNIGHT; }