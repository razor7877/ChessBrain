#include <iostream>

#include "game/humanPlayer.hpp"
#include "game/game.hpp"

HumanPlayer::HumanPlayer(bool whiteSide, Renderer* currentRenderer) : Player(whiteSide)
{
	this->isAiPlayer = false;
	this->currentRenderer = currentRenderer;
}

void HumanPlayer::playNextMove(Game* currentGame)
{
	
}

void HumanPlayer::updateInput(Game* currentGame, glm::vec2 clickedCase)
{
#ifdef DEBUG_MODE
	std::cout << "Active case: " << this->activeCase.x << "," << this->activeCase.y << "\n";
#endif
	
	if (this->activeCase != glm::vec2(-1.0f))
	{
		// Clicking on same case, cancel selection
		if (clickedCase == this->activeCase)
		{
			currentRenderer->setActiveCase(glm::vec2(-1.0f));
			this->activeCase = glm::vec2(-1.0f);
		}
		// If a case was clicked which isn't the same as the selected one, attempt move
		else if (currentGame->playerMove(this, this->activeCase.x, this->activeCase.y, clickedCase.x, clickedCase.y))
		{
			currentRenderer->setActiveCase(glm::vec2(-1.0f));
			this->activeCase = glm::vec2(-1.0f);
		}
			
	}
	// Click on valid case, select it
	else if (currentGame->isValidCaseClick(clickedCase))
	{
#ifdef DEBUG_MODE
		std::cout << "Selected case: " << clickedCase.x << "," << clickedCase.y << "\n";
#endif
		currentRenderer->setActiveCase(clickedCase);
		this->activeCase = clickedCase;
	}
}
