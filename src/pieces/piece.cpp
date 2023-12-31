#include "pieces/piece.hpp"

const std::map<PieceType, char> Piece::enumToString = {
	{ PieceType::PAWN, 'P' },
	{ PieceType::BISHOP, 'B' },
	{ PieceType::KING, 'K' },
	{ PieceType::QUEEN, 'Q' },
	{ PieceType::KNIGHT, 'N' },
	{ PieceType::ROOK, 'R' },
};

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