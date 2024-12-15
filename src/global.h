#pragma once

#include "../Dependencies/glm/glm.hpp"

#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 650

#define PIPE_SIZE_X 90
#define PIPE_SIZE_Y 462
#define PIPE_MIN_HEIGHT 230
#define PIPE_MAX_HEIGHT 450
#define PIPE_SPACING 200

#define PLAYER_SIZE 60
#define PLAYER_START_POSITION glm::vec2(100, 300)
#define PLAYER_MAX_ROTATE 80
#define PLAYER_MIN_ROTATE -10
#define GRAVITY 3000

#define COIN_SIZE 32

#define BACKGROUND_SPEED 60.f
#define GROUND_SPEED 202.f
#define PIPES_GEN_DELAY 2.f


#include "../Dependencies/glfw/glfw3.h"

#include "objects/Pipes.h"

#include <vector>

namespace gb {
	extern float deltaTime;
	extern float lastFrame;

	extern int windowX;
	extern int windowY;

	extern double mousePosX;
	extern double mousePosY;

	extern bool clicked;
	extern int action;
	extern bool paused;

	extern void* player;

	extern GLFWwindow* window;

	extern std::vector<Pipes*> pipes;

	extern const int randNum(const int min, const int max);
}