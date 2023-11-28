#include "game/board.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"

Board::Board()
{
	this->boxes = new Spot*[8];
	for (int i = 0; i < 8; i++)
	{
		this->boxes[i] = new Spot[8];
	}

	this->resetBoard();
}

void Board::resetBoard()
{
	// Black pieces
	this->boxes[0][7] = Spot(&Rook(false), 1, 8);
	this->boxes[1][7] = Spot(&Knight(false), 2, 8);
	this->boxes[2][7] = Spot(&Bishop(false), 3, 8);
	this->boxes[3][7] = Spot(&Queen(false), 4, 8);
	this->boxes[4][7] = Spot(&King(false), 5, 8);
	this->boxes[5][7] = Spot(&Bishop(false), 6, 8);
	this->boxes[6][7] = Spot(&Knight(false), 7, 8);
	this->boxes[7][7] = Spot(&Rook(false), 8, 8);
	this->boxes[0][7] = Spot(&Pawn(false), 1, 7);
	this->boxes[1][6] = Spot(&Pawn(false), 2, 7);
	this->boxes[2][6] = Spot(&Pawn(false), 3, 7);
	this->boxes[3][6] = Spot(&Pawn(false), 4, 7);
	this->boxes[4][6] = Spot(&Pawn(false), 5, 7);
	this->boxes[5][6] = Spot(&Pawn(false), 6, 7);
	this->boxes[6][6] = Spot(&Pawn(false), 7, 7);
	this->boxes[7][6] = Spot(&Pawn(false), 8, 7);

	// White pieces
	this->boxes[0][1] = Spot(&Rook(true), 1, 1);
	this->boxes[1][1] = Spot(&Knight(true), 2, 1);
	this->boxes[2][1] = Spot(&Bishop(true), 3, 1);
	this->boxes[3][1] = Spot(&Queen(true), 4, 1);
	this->boxes[4][1] = Spot(&King(true), 5, 1);
	this->boxes[5][1] = Spot(&Bishop(true), 6, 1);
	this->boxes[6][1] = Spot(&Knight(true), 7, 1);
	this->boxes[7][1] = Spot(&Rook(true), 8, 1);
	this->boxes[0][0] = Spot(&Pawn(true), 1, 2);
	this->boxes[1][0] = Spot(&Pawn(true), 2, 2);
	this->boxes[2][0] = Spot(&Pawn(true), 3, 2);
	this->boxes[3][0] = Spot(&Pawn(true), 4, 2);
	this->boxes[4][0] = Spot(&Pawn(true), 5, 2);
	this->boxes[5][0] = Spot(&Pawn(true), 6, 2);
	this->boxes[6][0] = Spot(&Pawn(true), 7, 2);
	this->boxes[7][0] = Spot(&Pawn(true), 8, 2);
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		delete this->boxes[i];
	}
	delete this->boxes;
}