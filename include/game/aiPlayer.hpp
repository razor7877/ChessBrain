#pragma once
#include <curl/curl.h>

#include "game/player.hpp"
#include "game/game.hpp"

class AiPlayer : public virtual Player
{
public:
	AiPlayer(bool whiteSide);
	~AiPlayer();
	void playNextMove(Game* currentGame);

private:
	CURL* curl;
};