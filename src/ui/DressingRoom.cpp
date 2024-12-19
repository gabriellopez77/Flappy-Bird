#include "DressingRoom.h"

#include "../Global.h"

DressingRoom::DressingRoom() :
	panel_image(452, 159, 57, 81),
	close_button(351, 118, 52, 29)
{
	panel_image.size = glm::ivec2(285, 407);
	panel_image.position = glm::vec2(SCREEN_WIDTH /2 - panel_image.size.x /2, SCREEN_HEIGHT /2 - panel_image.size.y /2);

	close_button.size = glm::ivec2(156, 100);
	close_button.position = glm::vec2(SCREEN_WIDTH / 2 - close_button.size.x / 2, SCREEN_HEIGHT - 200);
}

void DressingRoom::update() {
	close_button.update();

	if (gb::clicked && close_button.hover) {
		gb::dressingRoom = false;
		gb::start_screen = true;
	}
}

void DressingRoom::draw() {
	panel_image.draw();
	close_button.draw();
}