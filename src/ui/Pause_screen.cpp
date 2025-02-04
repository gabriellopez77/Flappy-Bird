#include "Pause_screen.h"

#include "../Global.h"

Pause::Pause() {
	id = ui::Pause_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	unpause_button.size = glm::vec2(52, 56);
	unpause_button.position = glm::vec2(SCREEN_WIDTH - unpause_button.size.x - 30, 30);
	unpause_button.setNormalizedTex(121, 321, 13, 14);
}

void Pause::update() {
	unpause_button.update();

	if (gb::clicked && unpause_button.hover)
		gb::changeCurrentInterface(ui::Hud_screen);
}

void Pause::draw() {
	unpause_button.draw();
}