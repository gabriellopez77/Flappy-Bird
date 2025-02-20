#include "Death_screen.h"

#include "../global.h"
#include "../objects/Player.h"

Death_screen::Death_screen() :
	playerBestScore_text(138, 323, 6, 7, 10),
	playerScore_text(138, 323, 6, 7, 10),
	coinCount_text(138, 323, 6, 7, 10)
{
	id = ui::Death_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	gameOver_image.size = glm::vec2(384, 100);
	gameOver_image.position = glm::vec2(SCREEN_SIZE_HALF.x, 100.f);
	gameOver_image.setNormalizedTex(395, 59, 96, 21);

	panel_image.size = glm::vec2(452, 228);
	panel_image.position = glm::vec2(SCREEN_SIZE_HALF.x, 320);
	panel_image.setNormalizedTex(3, 259, 113, 57);

	float panelX = panel_image.position.x;
	float panelY = panel_image.position.y;

	playerBestScore_text.size = glm::vec2(30, 35);
	playerBestScore_text.position = glm::vec2(panelX - 130.f, panelY + 10.f);

	playerScore_text.size = glm::vec2(30, 35);
	playerScore_text.position = glm::vec2(panelX, panelY + 10.f);

	coinCount_text.size = glm::vec2(30, 35);
	coinCount_text.position = glm::vec2(panelX + 130.f, panelY + 10.f);

	respawn_button.size = glm::vec2(156, 100);
	respawn_button.position = glm::vec2(SCREEN_SIZE_HALF.x - 88.f, SCREEN_SIZE.y - 250);
	respawn_button.setNormalizedTex(460, 483, 52, 29);

	house_button.size = glm::vec2(156, 100);
	house_button.position = glm::vec2(SCREEN_SIZE_HALF.x + 88.f, SCREEN_SIZE.y - 250);
	house_button.setNormalizedTex(460, 455, 52, 29);
}

void Death_screen::start() {
	Player* player = ((Player*)gb::player);

	if (gb::matchScore > player->bestScore)
		player->bestScore = gb::matchScore;

	playerBestScore_text.text = std::to_string(player->bestScore);
	coinCount_text.text = std::to_string(gb::matchCoinCount);
	playerScore_text.text = std::to_string(gb::matchScore);

	gb::currentStatus = status::Dead;
}

void Death_screen::update() {
	respawn_button.update();
	house_button.update();

	if (gb::clicked && respawn_button.hover) {
		gb::playerKill();
		gb::changeCurrentInterface(ui::Start_screen);
		gb::currentStatus = status::notStarted;
	}

	if (gb::clicked && house_button.hover) {
		gb::playerKill();
		gb::changeCurrentInterface(ui::Main_screen);
		gb::currentStatus = status::notStarted;
	}
}

void Death_screen::draw() {
	gameOver_image.draw();
	panel_image.draw();
	playerBestScore_text.draw();
	playerScore_text.draw();
	coinCount_text.draw();
	respawn_button.draw();
	house_button.draw();
}