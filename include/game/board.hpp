#pragma once
#include <glm/glm.hpp>

#include "main.hpp"
#include "game/spot.hpp"

class Spot;

// A class representing a board object, which contains an 8x8 matrix of spots for the chess pieces
class Board
{
public:
	/// <summary>
	/// Creates a new board, and sets up the default pieces for a chess game
	/// </summary>
	Board();
	~Board();
	/// <summary>
	/// Resets the board to it's starting state
	/// </summary>
	void resetBoard();
	/// <summary>
	/// Dumps the content of the board to the console (address of each spot and name of any piece there)
	/// </summary>
	void dumpBoardToConsole();
	/// <summary>
	/// Prints a grid of the current board status to the console
	/// </summary>
	void showBoardToConsole();
	/// <summary>
	/// Returns the spot at the given x,y coordinates
	/// </summary>
	/// <param name="x">The X coordinate</param>
	/// <param name="y">The Y coordinate</param>
	/// <returns></returns>
	Spot* getSpot(uint8_t x, uint8_t y);
	Spot* getSpot(glm::vec2 pos);

private:
	// A two dimensional array containing the spots
	// It's a row major array, the first index selects the row, the second one select the column
	Spot** boxes;
};
