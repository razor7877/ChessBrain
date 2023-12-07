#pragma once
#include <curl/curl.h>

#include "game/player.hpp"
#include "game/game.hpp"

class AiPlayer : public virtual Player
{
public:
	AiPlayer(bool whiteSide, std::string apiUrl = "http://localhost:10001/predict");
	~AiPlayer();
	virtual void playNextMove(Game* currentGame);

private:
	CURL* curl;
	std::string apiUrl;

	void playMoveFromSAN(Game* currentGame, std::string SAN);
};