#include "game/move.hpp"

Move::Move(Player player, Spot start, Spot end)
{
	this->player = player;
	this->start = start;
	this->end = end;
	this->pieceMoved = start.piece;
}

bool Move::isCastlingMove() { return this->castlingMove; }

void Move::setCastlingMove(bool castlingMove) { this->castlingMove = castlingMove; }