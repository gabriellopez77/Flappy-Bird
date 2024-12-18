#include "Death_screen.h"

#include "../global.h"
#include "../objects/Player.h"

Death_screen::Death_screen() {
	board_image = new GameObject(3, 259, 113, 57);
	board_image->size = glm::ivec2(452, 228);
	board_image->position = glm::vec2(SCREEN_WIDTH /2 - board_image->size.x /2, 250);

	playerScore_text = new Text(138, 323, 6, 7, 10);
	playerScore_text->size = glm::ivec2(30, 35);
	playerScore_text->position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore_text->text.size()) + 120, 315);

	gameOver_image = new GameObject(395, 59, 96, 21);
	gameOver_image->size = glm::ivec2(384, 100);
	gameOver_image->position = glm::ivec2((SCREEN_WIDTH / 2) - (gameOver_image->size.x / 2), 50);

	respawn_button = new Button(351, 118, 52, 29);
	respawn_button->size = glm::ivec2(156, 100);
	respawn_button->position = glm::ivec2((SCREEN_WIDTH / 2) - respawn_button->size.x - 10, SCREEN_HEIGHT - 300);

	house_button = new Button(404, 118, 52, 29);
	house_button->size = glm::vec2(156, 100);
	house_button->position = glm::ivec2(SCREEN_WIDTH /2 + 10, SCREEN_HEIGHT - 300);

	coinCount_text = new Text(138, 323, 6, 7, 10);
	coinCount_text->size = glm::ivec2(30, 35);
	coinCount_text->position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore_text->text.size()) + 120, 400);
}

void Death_screen::update() {
	respawn_button->update();
	house_button->update();
	gb::onScreen = true;
	gb::paused = true;

	if (gb::clicked && respawn_button->hover) {
		gb::playerKill();
		gb::beforeStart = true;
	}

	if (gb::clicked && house_button->hover) {
		gb::playerKill();
		gb::start_screen = true;
	}
}

void Death_screen::draw() {
	board_image->draw();
	gameOver_image->draw();
	respawn_button->draw();
	playerScore_text->draw();
	coinCount_text->draw();
	house_button->draw();
}