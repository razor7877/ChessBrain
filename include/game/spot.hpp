#pragma once
#include "pieces/piece.hpp"

class Piece;

class Spot
{
public:
	Piece* piece;
	int x;
	int y;
	Spot();
	Spot(Piece* piece, int x, int y);
};
