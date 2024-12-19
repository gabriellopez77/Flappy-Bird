#include "Global.h"

#include "objects/Player.h"

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
	bool dressingRoom = false;


	// player
	void* player = nullptr;
	void playerKill() {
		pipes.clear();
		((Player*)player)->coinCount = 0;
		((Player*)player)->score = 0;
		((Player*)player)->position = PLAYER_START_POSITION;
		((Player*)player)->rotate = 0.f;
		((Player*)player)->scoreDelay = 0.f;
		genPipesDelay = 0.f;
		paused = false;
		death_screen = false;
		started = false;
		onScreen = false;
	}


	// objects
	std::vector<Pipes*> pipes = std::vector<Pipes*>();


	// outros
	bool beforeStart = false;
	float genPipesDelay = 0.f;
	int randNum(const int min, const int max) {
		static std::random_device rd;
		static std::mt19937_64 gen = std::mt19937_64(rd());

		std::uniform_int_distribution rand_num(min, max);

		return rand_num(gen);
	}
}