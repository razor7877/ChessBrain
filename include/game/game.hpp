#pragma once
#include <vector>

#include "game/player.hpp"
#include "game/board.hpp"
#include "game/move.hpp"
#include "graphics/renderer.hpp"

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
	/// <summary>
	/// Creates a new game with two players
	/// </summary>
	/// <param name="p1">The first player</param>
	/// <param name="p2">The second player</param>
	Game(Renderer* renderer, Player* p1, Player* p2);
	~Game();
	/// <summary>
	/// Reinitialize the game's state
	/// </summary>
	void initialize();
	/// <summary>
	/// Returns whether the game is finished or not
	/// </summary>
	/// <returns>True if the game is finished, false otherwise</returns>
	bool isEnd();
	/// <summary>
	/// Returns the player whose turn it is to play
	/// </summary>
	/// <returns>The player that is currently playing their turn</returns>
	Player* getCurrentPlayer();
	/// <summary>
	/// Attempts to make a move from one spot to another for a given player
	/// </summary>
	/// <param name="player">The player that makes the move</param>
	/// <param name="startX">The X position of the starting spot</param>
	/// <param name="startY">The Y position of the starting spot</param>
	/// <param name="endX">The X position of the target spot</param>
	/// <param name="endY">The Y position of the target spot</param>
	/// <returns></returns>
	bool playerMove(Player* player, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
	bool isValidCaseClick(glm::vec2 selectedCase);
	std::string getFEN();

private:
	Renderer* renderer;
	Player* players[2]{};
	Board* board{};
	Player* currentTurn{};
	GameStatus status{};
	std::vector<Move*> movesPlayed{};

	bool makeMove(Move* move, Player* player);
};