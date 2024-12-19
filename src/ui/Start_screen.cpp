#include "Start_screen.h"

#include "../global.h"

Start_screen::Start_screen() :
	gameTitle_image(351, 91, 89, 24),
	start_button(351, 118, 52, 29),
	brush_button(457, 118, 52, 29)
{
	gameTitle_image.size = glm::ivec2(356, 96);
	gameTitle_image.position = glm::ivec2(SCREEN_WIDTH / 2 - gameTitle_image.size.x / 2, 50);

	start_button.size = glm::ivec2(156, 100);
	start_button.position = glm::ivec2(SCREEN_WIDTH / 2 - start_button.size.x - 10, SCREEN_HEIGHT - 300);

	brush_button.size = glm::ivec2(156, 100);
	brush_button.position = glm::vec2(SCREEN_WIDTH /2 + 10, SCREEN_HEIGHT - 300);
}

void Start_screen::update() {
	start_button.update();
	brush_button.update();
	gb::onScreen = true;

	if (gb::clicked && start_button.hover) {
		gb::start_screen = false;
		gb::onScreen = false;
		gb::beforeStart = true;
	}

	if (gb::clicked && brush_button.hover) {
		gb::dressingRoom = true;
		gb::start_screen = false;
	}
}

void Start_screen::draw() {
	start_button.draw();
	gameTitle_image.draw();
	brush_button.draw();
}