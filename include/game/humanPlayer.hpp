#pragma once
#include <glm/glm.hpp>

#include "game/player.hpp"
#include "game/game.hpp"
#include "graphics/renderer.hpp"

class HumanPlayer : public virtual Player
{
public:
	// Keep a reference to the renderer so that the player can update currently selected case
	Renderer* currentRenderer;

	HumanPlayer(bool whiteSide, Renderer* currentRenderer);
	void updateInput(Game* currentGame, glm::vec2 clickedCase);

private:
	glm::vec2 activeCase = glm::vec2(-1.0f);
};
