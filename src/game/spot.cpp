#include "game/spot.hpp"

Spot::Spot()
{
	this->piece = nullptr;
	this->x = 0;
	this->y = 0;
}

Spot::Spot(Piece* piece, int x, int y)
{
	this->piece = piece;
	this->x = x;
	this->y = y;
}