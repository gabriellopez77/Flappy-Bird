#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glfw/glfw3.h"

#include "objects/Pipes.h"
#include "InterfaceObject.h"

#include <vector>
#include <unordered_map>

inline constexpr int SCREEN_WIDTH = 800;
inline constexpr int SCREEN_HEIGHT = 800;

inline constexpr int PIPE_SIZE_X = 90;
inline constexpr int PIPE_SIZE_Y = 462;
inline constexpr int PIPE_MIN_HEIGHT = 250;
inline constexpr int PIPE_MAX_HEIGHT = SCREEN_HEIGHT - 160 - 40;
inline constexpr float PIPES_GEN_DELAY = 1.2f;
inline constexpr int PIPE_SPACING = 180;

inline constexpr int PLAYER_SIZE = 60;
inline constexpr glm::vec2 PLAYER_START_POSITION(200.f, 300.f);
inline constexpr int PLAYER_MAX_ROTATE = 90;
inline constexpr int PLAYER_MIN_ROTATE = -10;
inline constexpr int GRAVITY = 3000;
inline constexpr glm::vec4 hitBoxColor = glm::vec4(0.5f, 0.2f, 0.2f, 0.3f);

inline constexpr int COIN_SIZE = 32;

inline constexpr float BACKGROUND_SPEED = 60.f;
inline constexpr float BACKGROUND_ALPHA = 0.5f;
inline constexpr float GROUND_SPEED = 300.f;

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

	// player
	extern void* player;
	extern void playerKill();


	// objects
	extern std::vector<Pipes*> pipes;
	extern std::unordered_map<ui, InterfaceObject*> gui;


	// outros
	extern status currentStatus;
	extern float genPipesDelay;
	extern bool debugMode;

	// muda a interface ativa no momento e chama a fun�ao 'start'
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
}