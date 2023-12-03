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
	delete[] this->boxes;
}

void Board::resetBoard()
{
	// Black pieces
	this->boxes[7][0] = Spot(new Rook(false), 1, 8);
	this->boxes[7][1] = Spot(new Knight(false), 2, 8);
	this->boxes[7][2] = Spot(new Bishop(false), 3, 8);
	this->boxes[7][3] = Spot(new Queen(false), 4, 8);
	this->boxes[7][4] = Spot(new King(false), 5, 8);
	this->boxes[7][5] = Spot(new Bishop(false), 6, 8);
	this->boxes[7][6] = Spot(new Knight(false), 7, 8);
	this->boxes[7][7] = Spot(new Rook(false), 8, 8);
	this->boxes[6][0] = Spot(new Pawn(false), 1, 7);
	this->boxes[6][1] = Spot(new Pawn(false), 2, 7);
	this->boxes[6][2] = Spot(new Pawn(false), 3, 7);
	this->boxes[6][3] = Spot(new Pawn(false), 4, 7);
	this->boxes[6][4] = Spot(new Pawn(false), 5, 7);
	this->boxes[6][5] = Spot(new Pawn(false), 6, 7);
	this->boxes[6][6] = Spot(new Pawn(false), 7, 7);
	this->boxes[6][7] = Spot(new Pawn(false), 8, 7);

	// White pieces
	this->boxes[0][0] = Spot(new Rook(true), 1, 1);
	this->boxes[0][1] = Spot(new Knight(true), 2, 1);
	this->boxes[0][2] = Spot(new Bishop(true), 3, 1);
	this->boxes[0][3] = Spot(new Queen(true), 4, 1);
	this->boxes[0][4] = Spot(new King(true), 5, 1);
	this->boxes[0][5] = Spot(new Bishop(true), 6, 1);
	this->boxes[0][6] = Spot(new Knight(true), 7, 1);
	this->boxes[0][7] = Spot(new Rook(true), 8, 1);
	this->boxes[1][0] = Spot(new Pawn(true), 1, 2);
	this->boxes[1][1] = Spot(new Pawn(true), 2, 2);
	this->boxes[1][2] = Spot(new Pawn(true), 3, 2);
	this->boxes[1][3] = Spot(new Pawn(true), 4, 2);
	this->boxes[1][4] = Spot(new Pawn(true), 5, 2);
	this->boxes[1][5] = Spot(new Pawn(true), 6, 2);
	this->boxes[1][6] = Spot(new Pawn(true), 7, 2);
	this->boxes[1][7] = Spot(new Pawn(true), 8, 2);

	// Fill up the remaining board with empty spots
	for (int x = 2; x < 6; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			this->boxes[x][y] = Spot(nullptr, y + 1, x + 1);
		}
	}
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
	std::string board = "\n";
	for (int x = 7; x >= 0 ; x--)
	{
		board += "| ";
		for (int y = 0; y < 8; y++)
		{
			Spot* spot = this->getSpot(y, x);
			if (spot->piece == nullptr)
			{
				board += " - ";
			}
			else
			{
				PieceType type = spot->piece->getType();
				board += Piece::enumToString.at(type) + " ";
				board += spot->piece->isWhite() ? "0" : "1";
			}
			board += " | ";
		}
		board += "\n";
	}
	std::cout << board << "\n";
}

Spot* Board::getSpot(uint8_t x, uint8_t y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
	{
#ifdef DEBUG_MODE
		std::cout << "Attempted out of bounds getSpot() call with pos: " << x << "," << y << "\n";
		return nullptr;
#endif
	}

	return &this->boxes[y][x];
}

Spot* Board::getSpot(glm::vec2 pos)
{
	int x = (int)pos.x;
	int y = (int)pos.y;

	if (x < 0 || x > 7 || y < 0 || y > 7)
	{
#ifdef DEBUG_MODE
		std::cout << "Attempted out of bounds getSpot() call with pos: " << pos.x << "," << pos.y << "\n";
		return nullptr;
#endif
	}

	Spot s = this->boxes[y][x];
#ifdef DEBUG_MODE
	std::cout << "getSpot() call with pos: " << x << "," << pos.y << "\n";
	std::cout << "Returns spot with pos: " << s. x << "," << s.y << "\n";
#endif
	return &this->boxes[y][x];
}