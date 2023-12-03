#pragma once
#include <glm/glm.hpp>

// Enable this for more verbose information on what is happening
#define DEBUG_MODE

extern constexpr float caseSize = 1.0f / 8.0f;

void updatePlayerInput(glm::vec2 clickedCase);