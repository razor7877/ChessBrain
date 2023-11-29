#include <iostream>

#include "game/humanPlayer.hpp"


HumanPlayer::HumanPlayer(bool whiteSide)
{
	this->whiteSide = whiteSide;
	this->humanPlayer = true;
}

Move HumanPlayer::getNextMove()
{
	int x, y{};

	std::cout << "Select x value: ";
	std::cin >> x;
	std::cout << "Select y value: ";
	std::cin >> y;
}