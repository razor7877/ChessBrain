#include "game/spot.hpp"

Spot::Spot()
{
	
}

Spot::Spot(Piece* piece, int x, int y)
{
	this->piece = piece;
	this->x = x;
	this->y = y;
}