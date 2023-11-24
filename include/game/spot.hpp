#pragma once
#include "pieces/piece.hpp"

class Piece;

struct Spot
{
	Piece* piece;
	int x;
	int y;
};