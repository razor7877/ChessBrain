#pragma once
#include <vector>

#include "game/player.hpp"
#include "game/board.hpp"
#include "game/move.hpp"

enum class GameStatus
{
	ACTIVE,
	BLACK_WIN,
	WHITE_WIN,
	FORFEIT,
	STALEMATE,
	RESIGNATION,
};

class Game
{
public:
	Game();
	Game(Player p1, Player p2);
	bool isEnd();
	bool getStatus();
	void setStatus(GameStatus status);
	bool playerMove(Player player, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);

private:
	Player players[2]{};
	Board board{};
	Player currentTurn{};
	GameStatus status{};
	std::vector<Move> movesPlayed{};

	bool makeMove(Move move, Player player);
};