#pragma once
#include <map>
#include <string>

#include "game/board.hpp"
#include "game/spot.hpp"

class Board;
class Spot;

enum class PieceType
{
	PAWN,
	BISHOP,
	KING,
	QUEEN,
	KNIGHT,
	ROOK
};

// Represents a single chess piece
class Piece
{
public:
	const static std::map<PieceType, std::string> enumToString;

	Piece(bool white);
	bool isWhite();
	void setWhite(bool white);
	bool isKilled();
	void setKilled(bool killed);

	virtual bool canMove(Board board, Spot start, Spot end) = 0;
	virtual PieceType getType() = 0;

private:
	bool killed = false;
	bool white = false;
};
