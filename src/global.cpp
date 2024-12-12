#include "Global.h"

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

	GLFWwindow* window = nullptr;

	std::vector<Pipes*> pipes = std::vector<Pipes*>();
}