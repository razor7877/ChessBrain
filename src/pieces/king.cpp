#include <stdlib.h>

#include "pieces/king.hpp"

King::King(bool white) : Piece::Piece(white){}

bool King::canMove(Board board, Spot start, Spot end)
{
	return true;
}