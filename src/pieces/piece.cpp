#include "pieces/piece.hpp"

Piece::Piece(bool white)
{
	this->white = white;
}

bool Piece::isWhite()
{
	return this->white;
}

void Piece::setWhite(bool white)
{
	this->white = white;
}

bool Piece::isKilled()
{
	return this->killed;
}

void Piece::setKilled(bool killed)
{
	this->killed = killed;
}