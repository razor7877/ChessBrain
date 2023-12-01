#include "game/game.hpp"
#include "pieces/king.hpp"
#include <iostream>

Game::Game()
{

}

Game::Game(Player p1, Player p2)
{
	players[0] = p1;
	players[1] = p2;

	if (players[0].isWhiteSide())
		this->currentTurn = players[0];
	else
		this->currentTurn = players[1];
}

void Game::initialize()
{
	board.resetBoard();

	if (players[0].isWhiteSide())
		this->currentTurn = players[0];
	else
		this->currentTurn = players[1];

	movesPlayed.clear();
}

bool Game::playerMove(Player player, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	Spot startBox = board.getSpot(startX, startY);
	Spot endBox = board.getSpot(endX, endY);
	Move move = Move(player, startBox, endBox);

	return this->makeMove(move, player);
}

void Game::setupRenderer(Renderer renderer)
{
	this->board.showBoardToConsole();
	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			Spot spot = this->board.getSpot(x, y);
			if (spot.piece != nullptr)
			{
				renderer.addPiece(spot.piece, x, y);
			}
				
		}
	}
}

bool Game::isEnd() { return this->status != GameStatus::ACTIVE; }

bool Game::makeMove(Move move, Player player)
{
	Spot start = move.getStart();
	Spot end = move.getEnd();

	Piece* sourcePiece = start.piece;
	// Check if there is a piece in this spot
	if (sourcePiece == nullptr)
		return false;

	// Make sure this is the player's turn
	if (&player != &currentTurn)
		return false;

	// Make sure the player is playing a piece of the right color
	if (sourcePiece->isWhite() != player.isWhiteSide())
		return false;

	// Make sure the attempted move is valid
	if (!sourcePiece->canMove(board, start, end))
		return false;

	// Check if there was a kill
	Piece* destPiece = end.piece;
	if (destPiece != nullptr)
	{
		destPiece->setKilled(true);
		move.setPieceKilled(destPiece);
	}

	// TODO : Implement castling

	this->movesPlayed.push_back(move);

	// Move piece to the new spot
	end.piece = sourcePiece;

	// Remove piece from the old spot
	start.piece = nullptr;

	if (destPiece != nullptr && destPiece->getType() == PieceType::KING)
	{
		if (player.isWhiteSide())
			this->status = GameStatus::WHITE_WIN;
		else
			this->status = GameStatus::BLACK_WIN;
	}

	// Change turns
	if (&this->currentTurn == &players[0])
		this->currentTurn = players[1];
	else
		this->currentTurn = players[0];

	return true;
}