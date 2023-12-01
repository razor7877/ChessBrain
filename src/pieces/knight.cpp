#include <stdlib.h>

#include "pieces/knight.hpp"

Knight::Knight(bool white) : Piece::Piece(white){}

bool Knight::canMove(Board* board, Spot* start, Spot* end)
{
	return true;
}

PieceType Knight::getType() { return PieceType::KNIGHT; }