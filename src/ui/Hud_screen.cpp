#include "Hud_screen.h"

#include "../Global.h"

Hud::Hud() :
	coin_image(194, 258, 16, 16),
	coinCount_text(138, 323, 6, 7, 10),
	score_text(292, 158, 12, 18, 16)
{
	id = (int)ui::Hud_screen;
	gb::gui.insert(std::pair<int, InterfaceObject*>(id, this));

	coin_image.size = glm::ivec2(48);
	coin_image.position = glm::ivec2(20, 30);

	coinCount_text.size = glm::ivec2(30, 35);
	coinCount_text.position = glm::ivec2(71, 35);

	score_text.size = glm::ivec2(48, 72);
	score_text.position = glm::vec2((SCREEN_WIDTH / 2) - (24 * score_text.text.size()), 120);

}

void Hud::update() {

}

void Hud::draw() {
	coin_image.draw();
	score_text.draw();
	coinCount_text.draw();
}