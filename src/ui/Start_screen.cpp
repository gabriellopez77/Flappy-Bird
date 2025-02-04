#include "Start_screen.h"

#include "../global.h"
#include "../objects/Player.h"

Start_screen::Start_screen() {
	id = ui::Start_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	getReady_image.size = glm::vec2(368, 100);
	getReady_image.position = glm::vec2(SCREEN_WIDTH /2 - getReady_image.size.x /2, 50);
	getReady_image.setNormalizedTex(295, 59, 92, 25);

	clickToStart_image.size = glm::vec2(57 * 4, 49 * 4);
	clickToStart_image.position = glm::vec2(SCREEN_WIDTH / 2 - clickToStart_image.size.x / 2, 250);
	clickToStart_image.setNormalizedTex(292, 91, 57, 49);
}

void Start_screen::update() {
	gb::cursorState = glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);

	if (gb::clicked) {
		Player* pl = (Player*)gb::player;

		pl->groundCollided = false;
		pl->input(action::JUMP);
		gb::currentStatus = status::Started;
		gb::changeCurrentInterface(ui::Hud_screen);

	}
}

void Start_screen::draw() {
	getReady_image.draw();
	clickToStart_image.draw();
}