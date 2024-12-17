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

	respawn_button = new Button(354, 118, 52, 29);
	respawn_button->size = glm::ivec2(156, 87);
	respawn_button->position = glm::ivec2((SCREEN_WIDTH / 2) - (respawn_button->size.x / 2), 550);

	coinCount_text = new Text(138, 323, 6, 7, 10);
	coinCount_text->size = glm::ivec2(30, 35);
	coinCount_text->position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore_text->text.size()) + 120, 400);
}

void Death_screen::update() {
	respawn_button->update();

	if (gb::clicked && respawn_button->hover) {
		gb::pipes.clear();
		((Player*)gb::player)->coinCount = 0;
		((Player*)gb::player)->score = 0;
		((Player*)gb::player)->position = PLAYER_START_POSITION;
		gb::paused = false;
	}
}

void Death_screen::draw() {
	board_image->draw();
	gameOver_image->draw();
	respawn_button->draw();
	playerScore_text->draw();
	coinCount_text->draw();
}