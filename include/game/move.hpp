#pragma once
#include "game/player.hpp"
#include "game/spot.hpp"

class Player;

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