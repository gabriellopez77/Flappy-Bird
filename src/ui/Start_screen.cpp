#include "Start_screen.h"

#include "../global.h"
#include <iostream>
Start_screen::Start_screen() {
	id = ui::Start_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	getReady_image.size = glm::ivec2(368, 100);
	getReady_image.position = glm::vec2(SCREEN_WIDTH /2 - getReady_image.size.x /2, 50);
	getReady_image.setNormalizedTex(295, 59, 92, 25);

	clickToStart_image.size = glm::ivec2(57 * 4, 49 * 4);
	clickToStart_image.position = glm::vec2(SCREEN_WIDTH / 2 - clickToStart_image.size.x / 2, 250);
	clickToStart_image.setNormalizedTex(292, 91, 57, 49);
}

void Start_screen::update() {

}

void Start_screen::draw() {
	getReady_image.draw();
	clickToStart_image.draw();
}