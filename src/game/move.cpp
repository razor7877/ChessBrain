#include "game/move.hpp"

Move::Move(Player* player, Spot* start, Spot* end)
{
	this->player = player;
	this->start = start;
	this->end = end;
	this->pieceMoved = start->piece;
	this->pieceKilled = false;
}

Move::~Move()
{
	delete player;
	delete start;
	delete end;
	delete pieceMoved;
	delete pieceKilled;
}

bool Move::isCastlingMove() { return this->castlingMove; }

void Move::setCastlingMove(bool castlingMove) { this->castlingMove = castlingMove; }

Spot* Move::getStart() { return this->start; }
Spot* Move::getEnd() { return this->end; }
void Move::setPieceKilled(Piece* pieceKilled) { this->pieceKilled = pieceKilled; }