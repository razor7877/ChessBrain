#pragma once
#include <map>
#include <string>

#include "game/board.hpp"
#include "game/spot.hpp"

class Board;
class Spot;

// Represents one of each possible chess piece types
enum class PieceType
{
	PAWN,
	BISHOP,
	KING,
	QUEEN,
	KNIGHT,
	ROOK
};

// Represents a single chess piece (abstract class that actual pieces inherit from)
class Piece
{
public:
	// Maps each enum type to a respective string (KING maps to "K" etc.)
	const static std::map<PieceType, std::string> enumToString;

	Piece(bool white);
	bool isWhite();
	void setWhite(bool white);
	bool isKilled();
	void setKilled(bool killed);
	virtual bool canMove(Board* board, Spot* start, Spot* end) = 0;
	virtual PieceType getType() = 0;

private:
	bool killed = false;
	bool white = false;
};
