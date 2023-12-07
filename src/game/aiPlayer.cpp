#include <string>
#include <iostream>

#include "main.hpp"
#include "game/aiPlayer.hpp"

const std::map<char, int> letterToIndex = {
	{ 'a', 0 },
	{ 'b', 1 },
	{ 'c', 2 },
	{ 'd', 3 },
	{ 'e', 4 },
	{ 'f', 5 },
	{ 'g', 6 },
	{ 'h', 7 },
};

// Callback function to handle the response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
	size_t total_size = size * nmemb;
	output->append((char*)contents, total_size);
	return total_size;
}

AiPlayer::AiPlayer(bool whiteSide, std::string apiUrl) : Player(whiteSide)
{
	this->isAiPlayer = true;
	this->apiUrl = apiUrl;
	curl = curl_easy_init();
}

AiPlayer::~AiPlayer()
{
	curl_easy_cleanup(curl);
}

void AiPlayer::playNextMove(Game* currentGame)
{
#ifdef DEBUG_MODE
	if (currentGame->getCurrentPlayer() != this)
		std::cout << "AI playNextMove() called even though it is not currently it's turn to play\n";
#endif

	// Set the URL to query
	curl_easy_setopt(curl, CURLOPT_URL, this->apiUrl.c_str());

	// Set the POST data
	std::string post = "board=" + currentGame->getFEN();
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

	// Set the write callback function
	std::string response_data;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

	// Perform the request, res will get the return code
	CURLcode res = curl_easy_perform(curl);
	// Check for errors
	if (res != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return;
	}
	
	this->playMoveFromSAN(currentGame, response_data);
}

void AiPlayer::playMoveFromSAN(Game* currentGame, std::string SAN)
{
	if (SAN.length() != 4)
	{
#ifdef DEBUG_MODE
		std::cout << "Attempting to parse received SAN move with length != 4: " << SAN << "\n";
#endif
		return;
	}

	// In ASCII representation, digits start at 48, substracting 48 from the digit char code gives the int value
	// Letter values (x axis) are already mapped 0-7 but digit values (y axis) are mapped 1-8 so we substract 1
	int startX = letterToIndex.at(SAN[0]);
	int startY = (int)SAN[1] - 48 - 1;
	int endX = letterToIndex.at(SAN[2]);
	int endY = (int)SAN[3] - 48 - 1;

#ifdef DEBUG_MODE
	std::cout << "Attemping move from SAN start " << startX << "," << endX << " to " << startY << "," << endY << "\n";
#endif

	currentGame->playerMove(this, startX, startY, endX, endY);
}