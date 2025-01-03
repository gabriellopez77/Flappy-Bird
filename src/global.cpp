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
	double mousePosX = 0;
	double mousePosY = 0;
	GLFWcursor* cursorState = nullptr;


	// interfaces
	bool paused = false;
	bool onScreen = false;
	ui currentScreen = ui::Main_screen;

	// player
	void* player = nullptr;
	void playerKill() {
		Player* pl = ((Player*)player);

		pipes.clear();
		pl->coinCount += pl->matchCoinCount;
		pl->matchCoinCount = 0i16;
		pl->score = 0i16;
		pl->position = PLAYER_START_POSITION;
		pl->rotate = 0.f;
		genPipesDelay = 0.f;
	}


	// objects
	std::vector<Pipes*> pipes = std::vector<Pipes*>();
	std::unordered_map<ui, InterfaceObject*> gui;


	// outros
	stats currentStatus = stats::notStarted;
	float genPipesDelay = 0.f;

	void changeCurrentInterface(ui interface) {
		gui[interface]->start();
		currentScreen = interface;
	}

	int randNum(const int min, const int max) {
		static std::random_device rd;
		static std::mt19937_64 gen = std::mt19937_64(rd());

		std::uniform_int_distribution rand_num(min, max);

		return rand_num(gen);
	}

	float lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	bool chance(int percentage) {
		return randNum(0, 100) < percentage;
	}
}