#include "Start_screen.h"

#include "../global.h"

Start_screen::Start_screen() {
	gameTitle_image = new GameObject(351, 91, 89, 24);
	gameTitle_image->size = glm::ivec2(356, 96);
	gameTitle_image->position = glm::ivec2(SCREEN_WIDTH / 2 - gameTitle_image->size.x / 2, 50);

	start_button = new Button(354, 118, 52, 29);
	start_button->size = glm::ivec2(156, 87);
	start_button->position = glm::ivec2(SCREEN_WIDTH / 2 - start_button->size.x / 2, SCREEN_HEIGHT - 300);
}

void Start_screen::update() {
	start_button->update();
	gb::onScreen = true;

	if (gb::clicked && start_button->hover) {
		gb::start_screen = false;
		gb::onScreen = false;
	}
}

void Start_screen::draw() {
	start_button->draw();
	gameTitle_image->draw();
}