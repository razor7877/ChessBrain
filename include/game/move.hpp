#pragma once
#include "player.hpp"
#include "spot.hpp"

// A single move made during a game, containing information about the piece moved, by which player,
// the start and end position etc.
class Move
{
public:
	Move(Player player, Spot start, Spot end);
	bool isCastlingMove();
	void setCastlingMove(bool castlingMove);
	Spot getStart();
	Spot getEnd();
	void setPieceKilled(Piece* piece);

private:
	Player player;
	Spot start;
	Spot end;
	Piece* pieceMoved;
	Piece* pieceKilled;
	bool castlingMove = false;
};