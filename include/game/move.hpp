#pragma once
#include "player.hpp"
#include "spot.hpp"

class Move
{
public:
	Move(Player player, Spot start, Spot end);

private:
	Player player;
	Spot start;
	Spot end;
	Piece* pieceMoved;
	Piece* pieceKilled;
	bool castlingMove = false;
};