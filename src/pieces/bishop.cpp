#include <stdlib.h>

#include "pieces/bishop.hpp"

Bishop::Bishop(bool white) : Piece::Piece(white){}

bool Bishop::canMove(Board* board, Spot* start, Spot* end)
{
	return true;
}

PieceType Bishop::getType() { return PieceType::BISHOP; }