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
	// White pieces
	this->boxes[0][0] = Spot(&Rook(false), 1, 8);
	this->boxes[0][0] = Spot(&Rook(false), 2, 8);
	this->boxes[0][0] = Spot(&Rook(false), 3, 8);
	this->boxes[0][0] = Spot(&Rook(false), 4, 8);
	this->boxes[0][0] = Spot(&Rook(false), 5, 8);
	this->boxes[0][0] = Spot(&Rook(false), 6, 8);
	this->boxes[0][0] = Spot(&Rook(false), 7, 8);
	this->boxes[0][0] = Spot(&Rook(false), 8, 8);
	this->boxes[0][0] = Spot(&Rook(false), 1, 7);
	this->boxes[0][0] = Spot(&Rook(false), 2, 7);
	this->boxes[0][0] = Spot(&Rook(false), 3, 7);
	this->boxes[0][0] = Spot(&Rook(false), 4, 7);
	this->boxes[0][0] = Spot(&Rook(false), 5, 7);
	this->boxes[0][0] = Spot(&Rook(false), 6, 7);
	this->boxes[0][0] = Spot(&Rook(false), 7, 7);
	this->boxes[0][0] = Spot(&Rook(false), 8, 7);

	// Black pieces
	this->boxes[0][0] = Spot(&Rook(true), 1, 1);
	this->boxes[0][0] = Spot(&Rook(true), 2, 1);
	this->boxes[0][0] = Spot(&Rook(true), 3, 1);
	this->boxes[0][0] = Spot(&Rook(true), 4, 1);
	this->boxes[0][0] = Spot(&Rook(true), 5, 1);
	this->boxes[0][0] = Spot(&Rook(true), 6, 1);
	this->boxes[0][0] = Spot(&Rook(true), 7, 1);
	this->boxes[0][0] = Spot(&Rook(true), 8, 1);
	this->boxes[0][0] = Spot(&Rook(true), 1, 2);
	this->boxes[0][0] = Spot(&Rook(true), 2, 2);
	this->boxes[0][0] = Spot(&Rook(true), 3, 2);
	this->boxes[0][0] = Spot(&Rook(true), 4, 2);
	this->boxes[0][0] = Spot(&Rook(true), 5, 2);
	this->boxes[0][0] = Spot(&Rook(true), 6, 2);
	this->boxes[0][0] = Spot(&Rook(true), 7, 2);
	this->boxes[0][0] = Spot(&Rook(true), 8, 2);
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		delete this->boxes[i];
	}
	delete this->boxes;
}