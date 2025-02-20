#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glfw/glfw3.h"

#include "objects/Pipes.h"
#include "InterfaceObject.h"

#include <unordered_map>

constexpr glm::vec2 SCREEN_SIZE(800.f, 800.f);
constexpr glm::vec2 SCREEN_SIZE_HALF(SCREEN_SIZE.x / 2.f, SCREEN_SIZE.y / 2.f);

constexpr glm::vec2 GROUND_SIZE(SCREEN_SIZE.x, 168);
constexpr float BACKGROUND_SPEED = 60.f;
constexpr float BACKGROUND_ALPHA = 0.5f;
constexpr float GROUND_SPEED = 300.f;

constexpr float PIPE_SPAWN_POS_MIN = 475.f;
constexpr float PIPE_SPAWN_POS_MAX = 800.f;
constexpr glm::vec2 PIPE_SIZE(90.f, 462);
constexpr glm::vec2 PIPE_SIZE_HALF(PIPE_SIZE.x / 2.f, PIPE_SIZE.y / 2.f);
constexpr float PIPE_MIN_POS = 150.f;
constexpr float PIPE_MAX_POS = SCREEN_SIZE.y - GROUND_SIZE.y - 150.f;
constexpr glm::vec2 PIPE_SPACING(300.f, 180.f);

constexpr float PLAYER_SIZE = 60.f;
constexpr glm::vec2 PLAYER_START_POSITION(200.f, 300.f);
constexpr float PLAYER_MAX_ROTATE = 90.f;
constexpr float PLAYER_MIN_ROTATE = -10.f;
constexpr float GRAVITY = 3000.f;
constexpr glm::vec4 hitBoxColor(0.5f, 0.2f, 0.2f, 0.3f);

constexpr float COIN_SIZE = 32.f;


enum class status : char {
	notStarted,
	Started,
	Dead
};

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
	extern double mousePosX;
	extern double mousePosY;
	extern GLFWcursor* cursorState;


	// interfaces
	extern bool paused;
	extern bool onScreen;
	extern ui currentScreen;
	extern std::unordered_map<ui, InterfaceObject*> gui;

	// player
	extern void* player;
	extern int matchCoinCount;
	extern int matchScore;
	extern void playerKill();


	// outros
	extern status currentStatus;
	extern bool debugMode;

	// muda a interface ativa no momento e chama a funçao 'start'
	extern void changeCurrentInterface(ui interface);


	// math

	// retorna um numero aleatorio entre min e max
	extern int randNum(const int min, const int max);

	// retorna true se um numero aleatorio entre 0 e 100 for menor que a porcentagem, senao, false
	extern bool chance(int percentage);

	/*
		retorna um valor interpolado linearmente ente dois pontos
		@param[in] a: inicio
		@param[in] b: destino
		@param[in] t: porcentagem da distancia entre A e B

	*/
	extern float lerp(float a, float b, float t);

	extern float interpolation(float start, float end, float duration, float startTime);
}