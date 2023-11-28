#include <stdlib.h>

#include "pieces/rook.hpp"

Rook::Rook(bool white) : Piece::Piece(white){}

bool Rook::canMove(Board board, Spot start, Spot end)
{
	return true;
}

PieceType Rook::getType() { return PieceType::ROOK; }