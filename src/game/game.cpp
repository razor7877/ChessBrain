#include "main.hpp"

#ifdef DEBUG_MODE
#include <iostream>
#endif

#include "game/game.hpp"
#include "game/aiPlayer.hpp"
#include "pieces/king.hpp"

Game::Game()
{
	this->board = nullptr;
	this->renderer = nullptr;
}

Game::Game(Renderer* renderer, Player* p1, Player* p2)
{
	this->board = new Board();
	this->renderer = renderer;
	renderer->setupRenderer(board);

	this->players[0] = p1;
	this->players[1] = p2;

	if (players[0]->isWhiteSide())
		this->currentTurn = this->players[0];
	else
		this->currentTurn = this->players[1];
}

Game::~Game()
{
	delete board;

	for (Move* move : this->movesPlayed)
		delete move;
}

void Game::initialize()
{
	this->board->resetBoard();

	if (players[0]->isWhiteSide())
		this->currentTurn = players[0];
	else
		this->currentTurn = players[1];

	for (Move* move : this->movesPlayed)
		delete move;
	movesPlayed.clear();
}

bool Game::isEnd() { return this->status != GameStatus::ACTIVE; }

Player* Game::getCurrentPlayer() { return this->currentTurn; }

bool Game::playerMove(Player* player, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	Spot* startBox = board->getSpot(startX, startY);
	Spot* endBox = board->getSpot(endX, endY);
	Move* move = new Move(player, startBox, endBox);

	bool result = this->makeMove(move, player);
	if (!result)
		delete move;

	if (result)
	{
		std::cout << this->getFEN() << "\n";
		this->currentTurn->playNextMove(this);
	}

	return result;
}

bool Game::isValidCaseClick(glm::vec2 selectedCase)
{
	if (this->isEnd())
		return false;

	// Get the spot that was selected
	Spot* spot = board->getSpot(selectedCase);

	// Spot will be a nullptr if an out of bounds vector was passed as parameter
	if (spot == nullptr)
		return false;

	// If the spot doesn't contain a piece, ignore input
	if (spot->piece == nullptr)
		return false;

	// If the spot contains a piece corresponding to the other player's color, ignore input
	if (spot->piece->isWhite() != currentTurn->isWhiteSide())
		return false;

	return true;
}

std::string Game::getFEN()
{
	std::string FEN = this->board->getFEN();

	// Add current turn info
	if (this->currentTurn->isWhiteSide())
		FEN += " w";
	else
		FEN += " b";

	// TODO : Castling rights FEN
	FEN += " -";

	// TODO : En passant FEN
	FEN += " -";

	// TODO : Half move clock
	FEN += " 0";

	// TODO : Fullmove number
	FEN += " 0";

	return FEN;
}

bool Game::makeMove(Move* move, Player* player)
{
	// Don't make any moves if the game is finished
	if (this->isEnd())
		return false;

#ifdef DEBUG_MODE
	std::cout << "Attempting move\n";
#endif
	Spot* start = move->getStart();
	Spot* end = move->getEnd();

	Piece* sourcePiece = start->piece;
	// Check if there is a piece in this spot
	if (sourcePiece == nullptr)
	{
#ifdef DEBUG_MODE
		std::cout << "No piece at source\n";
#endif
		return false;
	}

	// Make sure this is the player's turn
	if (player != currentTurn)
	{
#ifdef DEBUG_MODE
		std::cout << "Wrong player attempting to play\n";
#endif
		return false;
	}
	std::cout << "Piece color: " << sourcePiece->isWhite() << "\n";
	std::cout << "Player color: " << player->isWhiteSide() << "\n";
	// Make sure the player is playing a piece of the right color
	if (sourcePiece->isWhite() != player->isWhiteSide())
	{
#ifdef DEBUG_MODE
		std::cout << "Attempted to move wrong colored piece\n";
#endif
		return false;
	}
	
	// Make sure the attempted move is valid
	if (!sourcePiece->canMove(board, start, end))
	{
		return false;
	}

	// At this point, we have successfully made a move
#ifdef DEBUG_MODE
	std::cout << "Successful move\n";
#endif

	// Check if there was a kill
	Piece* destPiece = end->piece;
	if (destPiece != nullptr)
	{
#ifdef DEBUG_MODE
		std::cout << "Successful kill on color: " << destPiece->isWhite() << "\n";
#endif
		destPiece->setKilled(true);
		move->setPieceKilled(destPiece);
		renderer->deletePiece(destPiece);
	}

	// TODO : Implement castling

	this->movesPlayed.push_back(move);

	// Move piece to the new spot
	end->piece = sourcePiece;
	// Update the renderer
	renderer->movePiece(sourcePiece, end->x - 1, end->y - 1);

	// Remove piece from the old spot
	start->piece = nullptr;

	// Check if king was killed and change game state if so
	if (destPiece != nullptr && destPiece->getType() == PieceType::KING)
	{
#ifdef DEBUG_MODE
		std::cout << "King killed, game finished\n";
#endif
		if (player->isWhiteSide())
			this->status = GameStatus::WHITE_WIN;
		else
			this->status = GameStatus::BLACK_WIN;
	}

	// Change turns
	if (this->currentTurn == players[0])
	{
		this->currentTurn = players[1];
	}
	else
	{
		this->currentTurn = players[0];
	}

	return true;
}