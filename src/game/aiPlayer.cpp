#include <string>

#include "game/aiPlayer.hpp"

AiPlayer::AiPlayer(bool whiteSide) : Player(whiteSide)
{
	CURLcode res;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:10001/predict");
		// Set the POST data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "key1=value1&key2=value2");

		// Perform the request, res will get the return code
		res = curl_easy_perform(curl);
		// Check for errors
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
	}
}

AiPlayer::~AiPlayer()
{
	curl_easy_cleanup(curl);
}

void AiPlayer::playNextMove(Game* currentGame)
{
	CURLcode res;

	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:10001/predict");
	// Set the POST data
	std::string post = "board=" + currentGame->getFEN();
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

	// Perform the request, res will get the return code
	res = curl_easy_perform(curl);
	// Check for errors
	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
}