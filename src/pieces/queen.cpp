#include <stdlib.h>

#include "pieces/queen.hpp"

Queen::Queen(bool white) : Piece::Piece(white){}

bool Queen::canMove(Board board, Spot start, Spot end)
{
	return true;
}