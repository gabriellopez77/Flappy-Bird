#include "Global.h"

#include <random>

namespace gb {
	// dt
	float deltaTime = 0.f;
	float lastFrame = 0.f;


	// window
	int windowX = 450;
	int windowY = 650;
	GLFWwindow* window = nullptr;


	// mouse
	bool clicked = false;
	int action = 0;
	double mousePosX = 0;
	double mousePosY = 0;
	GLFWcursor* cursorState = nullptr;


	// interfaces
	bool paused = false;
	bool started = false;
	bool onScreen = false;
	bool start_screen = true;
	bool death_screen = false;


	// player
	void* player = nullptr;


	// objects
	std::vector<Pipes*> pipes = std::vector<Pipes*>();


	// utils
	const int randNum(const int min, const int max) {
		static std::random_device rd;
		static std::mt19937 gen = std::mt19937(rd());

		std::uniform_int_distribution rand_num(min, max);

		return rand_num(gen);
	}
}