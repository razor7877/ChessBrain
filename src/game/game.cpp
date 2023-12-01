#include "main.hpp"

#ifdef DEBUG_MODE
#include <iostream>
#endif

#include "game/game.hpp"
#include "pieces/king.hpp"

Game::Game()
{
	this->board = nullptr;
	this->renderer = nullptr;
	this->lastSelectedSpot = nullptr;
}

Game::Game(Player* p1, Player* p2)
{
	this->board = new Board();
	this->renderer = new Renderer();
	this->setupRenderer();
	this->lastSelectedSpot = nullptr;

	this->players[0] = p1;
	this->players[1] = p2;

	if (players[0]->isWhiteSide())
		this->currentTurn = this->players[0];
	else
		this->currentTurn = this->players[1];
}

Game::~Game()
{
	delete renderer;
	delete board;
	delete currentTurn;
	delete lastSelectedSpot;

	for (Player* player : this->players)
		delete player;

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

	movesPlayed.clear();
}

bool Game::isEnd() { return this->status != GameStatus::ACTIVE; }

bool Game::playerMove(Player* player, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY)
{
	Spot* startBox = board->getSpot(startX, startY);
	Spot* endBox = board->getSpot(endX, endY);
	Move* move = new Move(player, startBox, endBox);

	bool result = this->makeMove(move, player);
	if (!result)
		delete move;

	return result;
}

void Game::setupRenderer()
{
	this->renderer->clearSprites();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Spot* spot = this->board->getSpot(x, y);
			if (spot->piece != nullptr)
			{
#ifdef DEBUG_MODE
				std::cout << "Piece at " << x << " " << y << "\n";
#endif
				this->renderer->addPiece(spot->piece, x, y);
			}
				
		}
	}
	board->showBoardToConsole();
}

void Game::drawFrame()
{
	this->renderer->drawFrame();
}

void Game::sendPlayerInput(glm::vec2 activeCase)
{
#ifdef DEBUG_MODE
	std::cout << "Active case: " << activeCase.x << "," << activeCase.y << "\n";
#endif
	// Get the spot that was selected
	Spot* spot = board->getSpot(activeCase);

	// If clicking again on same spot, cancel selection
#ifdef DEBUG_MODE
	std::cout << "Target spot: " << spot->x << "," << spot->y << "\n";
	std::cout << "Last spot: " << lastSelectedSpot << " | Equals nullptr?: " << (lastSelectedSpot == nullptr) << "\n";
#endif
	if (lastSelectedSpot != nullptr && lastSelectedSpot->x == spot->x && lastSelectedSpot->y == spot->y)
	{
		lastSelectedSpot = nullptr;
		// Set selected case outside of board
		this->renderer->boardShader->use().setVec2("activeCase", glm::vec2(-1.0f));
		return;
	}

	// If a piece was selected, then this is an attempt to make a move
	if (lastSelectedSpot != nullptr)
	{
		Move* m = new Move(this->currentTurn, lastSelectedSpot, spot);
		// Attempt a move
		if (makeMove(m, this->currentTurn))
		{
			// If successful, reset selection
			lastSelectedSpot = nullptr;
			this->renderer->boardShader->use().setVec2("activeCase", glm::vec2(-1.0f));
		}
		else
		{
#ifdef DEBUG_MODE
			std::cout << "Failed move\n";
#endif
		}
		
		return;
	}

	// If the spot doesn't contain a piece, ignore input
	if (spot->piece == nullptr)
		return;

	// If the spot contains a piece corresponding to the other player's color, ignore input
	if (spot->piece->isWhite() != currentTurn->isWhiteSide())
		return;

	lastSelectedSpot = spot;
	// Show the selected spot on the board
	this->renderer->boardShader->use().setVec2("activeCase", activeCase);
}

bool Game::makeMove(Move* move, Player* player)
{
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
	lastSelectedSpot = nullptr;

	// Check if there was a kill
	Piece* destPiece = end->piece;
	if (destPiece != nullptr)
	{
		destPiece->setKilled(true);
		move->setPieceKilled(destPiece);
	}

	// TODO : Implement castling

	this->movesPlayed.push_back(move);

	// Move piece to the new spot
	end->piece = sourcePiece;

	// Remove piece from the old spot
	start->piece = nullptr;

	// Check if king was killed and change game state if so
	if (destPiece != nullptr && destPiece->getType() == PieceType::KING)
	{
		if (player->isWhiteSide())
			this->status = GameStatus::WHITE_WIN;
		else
			this->status = GameStatus::BLACK_WIN;
	}

	// Change turns
	if (this->currentTurn == players[0])
		this->currentTurn = players[1];
	else
		this->currentTurn = players[0];

	this->setupRenderer();

	return true;
}