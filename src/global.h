#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glfw/glfw3.h"

#include "objects/Pipes.h"
#include "InterfaceObject.h"

#include <vector>
#include <map>
#include <unordered_map>

#define SCREEN_WIDTH 950
#define SCREEN_HEIGHT 850

#define PIPE_SIZE_X 90
#define PIPE_SIZE_Y 462
#define PIPE_MIN_HEIGHT 250
#define PIPE_MAX_HEIGHT 650
#define PIPES_GEN_DELAY 1.6f
#define PIPE_SPACING 200

#define PLAYER_SIZE 60
#define PLAYER_START_POSITION glm::vec2(100, 300)
#define PLAYER_MAX_ROTATE 80
#define PLAYER_MIN_ROTATE -10
#define GRAVITY 3000

#define COIN_SIZE 32

#define BACKGROUND_SPEED 60.f
#define GROUND_SPEED 230.f


namespace gb {
	// dt
	extern float deltaTime;
	extern float lastFrame;


	// window
	extern int windowX;
	extern int windowY;
	extern GLFWwindow* window;


	// mouse
	extern bool clicked;
	extern int action;
	extern double mousePosX;
	extern double mousePosY;
	extern GLFWcursor* cursorState;


	// interfaces
	extern bool paused;
	extern bool running;
	extern bool onScreen;
	extern int currentScreen;

	// player
	extern void* player;
	extern void playerKill();


	// objects
	extern std::vector<Pipes*> pipes;
	extern std::unordered_map<int, InterfaceObject*> gui;


	// outros
	extern bool beforeStart;
	extern float genPipesDelay;
	extern int randNum(const int min, const int max);
	extern float lerp(float a, float b, float t);
}