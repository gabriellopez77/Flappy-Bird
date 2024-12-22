#include "DressingRoom.h"

#include "../Global.h"

DressingRoom::DressingRoom() :
	panel_image(235, 455, 113, 57),
	close_button(460, 483, 52, 29),
	buyItem1_button(349, 498, 37, 14),
	buyItem2_button(349, 498, 37, 14),
	buyItem3_button(349, 498, 37, 14),
	coinCount_text(138, 323, 6, 7, 10),
	itemPrice1_text(138, 323, 6, 7, 10),
	itemPrice2_text(138, 323, 6, 7, 10),
	itemPrice3_text(138, 323, 6, 7, 10)
{
	id = (int)ui::DressingRoom_screen;
	gb::gui.insert(std::pair<int, InterfaceObject*>(id, this));

	panel_image.size = glm::ivec2(452, 228);
	panel_image.position = glm::vec2(SCREEN_WIDTH /2 - panel_image.size.x /2, SCREEN_HEIGHT /2 - panel_image.size.y /2);

	close_button.size = glm::ivec2(156, 100);
	close_button.position = glm::vec2(SCREEN_WIDTH / 2 - close_button.size.x / 2, SCREEN_HEIGHT - 200);

	coinCount_text.size = glm::ivec2(30, 35);
	coinCount_text.position = glm::vec2(400, 220);

	buyItem1_button.size = glm::ivec2(111, 42);
	buyItem1_button.position = glm::vec2(210, 450);

	buyItem2_button.size = glm::ivec2(111, 42);
	buyItem2_button.position = glm::vec2(buyItem1_button.position.x + buyItem1_button.size.x +20, 450);

	buyItem3_button.size = glm::ivec2(111, 42);
	buyItem3_button.position = glm::vec2(buyItem2_button.position.x + buyItem2_button.size.x + 20, 450);
}

void DressingRoom::update() {
	close_button.update();
	buyItem1_button.update();
	buyItem2_button.update();
	buyItem3_button.update();

	if (gb::clicked && close_button.hover) {
		gb::currentScreen = (int)ui::Main_screen;
	}
}

void DressingRoom::draw() {
	panel_image.draw();
	close_button.draw();
	coinCount_text.draw();
	buyItem1_button.draw();
	buyItem2_button.draw();
	buyItem3_button.draw();
}