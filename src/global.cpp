#include "Global.h"

#include <random>

namespace gb {
	float deltaTime = 0.f;
	float lastFrame = 0.f;

	int windowX = 450;
	int windowY = 650;

	double mousePosX = 0;
	double mousePosY = 0;

	bool clicked = false;
	int action = 0;
	bool paused = true;

	void* player = nullptr;
	GLFWwindow* window = nullptr;

	std::vector<Pipes*> pipes = std::vector<Pipes*>();

	const int randNum(const int min, const int max) {
		static std::random_device rd;
		static std::mt19937 gen = std::mt19937(rd());

		std::uniform_int_distribution rand_num(min, max);

		return rand_num(gen);
	}
}