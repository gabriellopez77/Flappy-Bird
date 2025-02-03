#include "Hud_screen.h"

#include "../Global.h"
#include "../objects/Player.h"

Hud::Hud() :
	coinCount_text(138, 323, 6, 7, 10),
	score_text(292, 158, 12, 18, 16)
{
	id = ui::Hud_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	coin_image.size = glm::ivec2(48);
	coin_image.position = glm::ivec2(20, 30);
	coin_image.setNormalizedTex(194, 258, 16, 16);

	pause_button.size = glm::ivec2(52, 56);
	pause_button.position = glm::vec2(SCREEN_WIDTH - pause_button.size.x - 30, 30);
	pause_button.setNormalizedTex(121, 306, 13, 14);

	coinCount_text.size = glm::ivec2(30, 35);
	coinCount_text.position = glm::ivec2(71, 35);

	score_text.size = glm::ivec2(48, 72);
	score_text.position = glm::vec2((SCREEN_WIDTH / 2) - (24 * score_text.text.size()), 120);
}

void Hud::start() {

}

void Hud::update() {
	pause_button.update();

	if (gb::clicked && pause_button.hover)
		if (gb::currentStatus != status::Dead)
			gb::changeCurrentInterface(ui::Pause_screen);

	static const Player* pl = ((Player*)gb::player);

	coinCount_text.text = std::to_string(pl->matchCoinCount);
	score_text.text = std::to_string(pl->score);
	score_text.position.x = (SCREEN_WIDTH / 2) - (24 * score_text.text.size());
}

void Hud::draw() {
	coin_image.draw();
	pause_button.draw();
	score_text.draw();
	coinCount_text.draw();
}