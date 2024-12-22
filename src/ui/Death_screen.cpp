#include "Death_screen.h"

#include "../global.h"
#include "../objects/Player.h"

Death_screen::Death_screen() :
	panel_image(3, 259, 113, 57),
	playerScore_text(138, 323, 6, 7, 10),
	gameOver_image(395, 59, 96, 21),
	respawn_button(460, 483, 52, 29),
	house_button(460, 455, 52, 29),
	coinCount_text(138, 323, 6, 7, 10)
{
	id = (int)ui::Death_screen;
	gb::gui.insert(std::pair<int, InterfaceObject*>(id, this));

	panel_image.size = glm::ivec2(452, 228);
	panel_image.position = glm::vec2(SCREEN_WIDTH /2 - panel_image.size.x /2, 250);

	playerScore_text.size = glm::ivec2(30, 35);
	playerScore_text.position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore_text.text.size()) + 120, 315);

	gameOver_image.size = glm::ivec2(384, 100);
	gameOver_image.position = glm::ivec2((SCREEN_WIDTH / 2) - (gameOver_image.size.x / 2), 50);

	respawn_button.size = glm::ivec2(156, 100);
	respawn_button.position = glm::ivec2((SCREEN_WIDTH / 2) - respawn_button.size.x - 10, SCREEN_HEIGHT - 300);

	house_button.size = glm::vec2(156, 100);
	house_button.position = glm::ivec2(SCREEN_WIDTH /2 + 10, SCREEN_HEIGHT - 300);

	coinCount_text.size = glm::ivec2(30, 35);
	coinCount_text.position = glm::vec2((SCREEN_WIDTH / 2) - (24 * playerScore_text.text.size()) + 120, 400);

}

void Death_screen::update() {
	respawn_button.update();
	house_button.update();

	if (gb::clicked && respawn_button.hover) {
		gb::playerKill();
		gb::currentScreen = (int)ui::Start_screen;
		gb::currentStatus = (char)stats::Starting;
	}

	if (gb::clicked && house_button.hover) {
		gb::playerKill();
		gb::currentScreen = (int)ui::Main_screen;
		gb::currentStatus = (char)stats::notStarted;
	}
}

void Death_screen::draw() {
	panel_image.draw();
	gameOver_image.draw();
	respawn_button.draw();
	playerScore_text.draw();
	coinCount_text.draw();
	house_button.draw();
}