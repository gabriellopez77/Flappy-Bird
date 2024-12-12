#include "global.h"

namespace gb {
	float deltaTime = 0.f;
	float lastFrame = 0.f;

	int windowX = 450;
	int windowY = 650;

	bool paused = false;

	GLFWwindow* window = nullptr;

	std::vector<Pipes*> pipes = std::vector<Pipes*>();
}