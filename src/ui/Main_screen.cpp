#include "Main_screen.h"

#include "../Global.h"
#include "../objects/Player.h"

Main_screen::Main_screen() {
	id = ui::Main_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	gameTitle_image.size = glm::vec2(356, 96);
	gameTitle_image.position = glm::vec2(SCREEN_SIZE_HALF.x - gameTitle_image.size.x / 2.f, 50.f);
	gameTitle_image.setNormalizedTex(351, 91, 89, 24);

	start_button.size = BUTTONS_SIZE;
	start_button.position = glm::vec2(SCREEN_SIZE_HALF.x - BUTTONS_SIZE.x / 2.f - 88.f, SCREEN_SIZE.y - 300);
	start_button.setNormalizedTex(460, 483, 52, 29);

	brush_button.size = BUTTONS_SIZE;
	brush_button.position = glm::vec2(SCREEN_SIZE_HALF.x - BUTTONS_SIZE.x /2.f + 88.f, SCREEN_SIZE.y - 300);
	brush_button.setNormalizedTex(460, 427, 52, 29);

	exit_button.size = BUTTONS_SIZE;
	exit_button.position = glm::vec2(SCREEN_SIZE_HALF.x - BUTTONS_SIZE.x /2.f, SCREEN_SIZE.y - 180);
	exit_button.setNormalizedTex(460, 399, 52, 29);

	versionName_image.size = glm::vec2(57 * 4, 5 * 4);
	versionName_image.position = glm::vec2(10.f, SCREEN_SIZE.x - versionName_image.size.y - 10.f);
	versionName_image.setNormalizedTex(443, 92, 57, 5);

	versionNumber_image.size = glm::vec2(19 * 4, 7 * 4);
	versionNumber_image.position = glm::vec2(SCREEN_SIZE.x - versionNumber_image.size.x - 10.f, SCREEN_SIZE.y - versionNumber_image.size.y - 10.f);
	versionNumber_image.setNormalizedTex(443, 98, 19, 7);
}

void Main_screen::start() {

}

void Main_screen::update() {
	start_button.update();
	brush_button.update();
	exit_button.update();

	if (gb::clicked && start_button.hover) {
		gb::changeCurrentInterface(ui::Start_screen);
	}

	else if (gb::clicked && brush_button.hover) {
		gb::changeCurrentInterface(ui::DressingRoom_screen);
	}

	else if (gb::clicked && exit_button.hover)
		glfwSetWindowShouldClose(gb::window, true);
}

void Main_screen::draw() {
	start_button.draw();
	gameTitle_image.draw();
	brush_button.draw();
	exit_button.draw();
	versionName_image.draw();
	versionNumber_image.draw();
}