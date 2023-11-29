#include "game/board.hpp"
#include "pieces/bishop.hpp"
#include "pieces/king.hpp"
#include "pieces/knight.hpp"
#include "pieces/pawn.hpp"
#include "pieces/queen.hpp"
#include "pieces/rook.hpp"
#include <iostream>

Board::Board()
{
	this->boxes = new Spot*[8];
	for (int i = 0; i < 8; i++)
	{
		this->boxes[i] = new Spot[8];
	}

	this->resetBoard();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		delete this->boxes[i];
	}
	delete this->boxes;
}

void Board::resetBoard()
{
	// Black pieces
	this->boxes[7][0] = Spot(&Rook(false), 1, 8);
	this->boxes[7][1] = Spot(&Knight(false), 2, 8);
	this->boxes[7][2] = Spot(&Bishop(false), 3, 8);
	this->boxes[7][3] = Spot(&Queen(false), 4, 8);
	this->boxes[7][4] = Spot(&King(false), 5, 8);
	this->boxes[7][5] = Spot(&Bishop(false), 6, 8);
	this->boxes[7][6] = Spot(&Knight(false), 7, 8);
	this->boxes[7][7] = Spot(&Rook(false), 8, 8);
	this->boxes[6][0] = Spot(&Pawn(false), 1, 7);
	this->boxes[6][1] = Spot(&Pawn(false), 2, 7);
	this->boxes[6][2] = Spot(&Pawn(false), 3, 7);
	this->boxes[6][3] = Spot(&Pawn(false), 4, 7);
	this->boxes[6][4] = Spot(&Pawn(false), 5, 7);
	this->boxes[6][5] = Spot(&Pawn(false), 6, 7);
	this->boxes[6][6] = Spot(&Pawn(false), 7, 7);
	this->boxes[6][7] = Spot(&Pawn(false), 8, 7);

	// White pieces
	this->boxes[0][0] = Spot(&Rook(true), 1, 1);
	this->boxes[0][1] = Spot(&Knight(true), 2, 1);
	this->boxes[0][2] = Spot(&Bishop(true), 3, 1);
	this->boxes[0][3] = Spot(&Queen(true), 4, 1);
	this->boxes[0][4] = Spot(&King(true), 5, 1);
	this->boxes[0][5] = Spot(&Bishop(true), 6, 1);
	this->boxes[0][6] = Spot(&Knight(true), 7, 1);
	this->boxes[0][7] = Spot(&Rook(true), 8, 1);
	this->boxes[1][0] = Spot(&Pawn(true), 1, 2);
	this->boxes[1][1] = Spot(&Pawn(true), 2, 2);
	this->boxes[1][2] = Spot(&Pawn(true), 3, 2);
	this->boxes[1][3] = Spot(&Pawn(true), 4, 2);
	this->boxes[1][4] = Spot(&Pawn(true), 5, 2);
	this->boxes[1][5] = Spot(&Pawn(true), 6, 2);
	this->boxes[1][6] = Spot(&Pawn(true), 7, 2);
	this->boxes[1][7] = Spot(&Pawn(true), 8, 2);

	// Fill up the remaining board with empty spots
	for (int x = 2; x < 6; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			this->boxes[x][y] = Spot(nullptr, x + 1, y + 1);
		}
	}

	//this->dumpBoardToConsole();
	this->showBoardToConsole();
}

void Board::dumpBoardToConsole()
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Spot spot = this->boxes[x][y];
			std::string type = "Empty";
			// Make sure this is not an empty spot
			if (spot.piece != nullptr)
			{
				switch (spot.piece->getType())
				{
				case PieceType::PAWN:
					type = "Pawn";
					break;
				case PieceType::BISHOP:
					type = "Bishop";
					break;
				case PieceType::KING:
					type = "King";
					break;
				case PieceType::QUEEN:
					type = "Queen";
					break;
				case PieceType::KNIGHT:
					type = "Knight";
					break;
				case PieceType::ROOK:
					type = "Rook";
					break;
				default:
					type = "Error";
					break;
				}
			}
			printf("Spot at (%d,%d): adr %x name %s\n", spot.x, spot.y, (int)spot.piece, type.c_str());
		}
	}
}

void Board::showBoardToConsole()
{
	for (int x = 0; x < 8; x++)
	{
		std::string row = "";
		for (int y = 0; y < 8; y++)
		{
			Spot spot = this->getSpot(y, x);
			if (spot.piece == nullptr)
			{
				row += "- ";
			}
			else
			{
				PieceType type = spot.piece->getType();
				row += Piece::enumToString.at(type) + " ";
			}
		}
		std::cout << row << "\n";
	}
}

Spot Board::getSpot(int x, int y)
{
	return this->boxes[y][x];
}