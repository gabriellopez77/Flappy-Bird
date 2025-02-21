#include "Hud_screen.h"

#include "../Global.h"
#include "../objects/Player.h"

Hud::Hud() :
	coinCount_text(138, 323, 6, 7, 10),
	score_text(292, 158, 12, 18, 16)
{
	id = ui::Hud_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	coin_image.size = glm::vec2(48);
	coin_image.position = glm::vec2(40.f, 40.f);
	coin_image.setNormalizedTex(194, 258, 16, 16);

	coinCount_text.size = glm::vec2(30, 35);
	coinCount_text.position = glm::vec2(coin_image.position.x + 60.f, 50.f);

	score_text.size = glm::vec2(48, 72);
	score_text.position = glm::vec2(SCREEN_SIZE_HALF.x - (24 * score_text.text.size()), 120);

	pause_button.size = glm::vec2(52, 56);
	pause_button.position = glm::vec2(SCREEN_SIZE.x - pause_button.size.x - 30.f, 30);
	pause_button.setNormalizedTex(121, 306, 13, 14);
}

void Hud::start() {

}

void Hud::update() {
	pause_button.update();

	if (gb::clicked && pause_button.hover)
		if (gb::currentStatus != status::Dead)
			gb::changeCurrentInterface(ui::Pause_screen);

	// atualiza os textos somente se ouver uma alteracao. (para evitar alocacoes desnecessarias de memoria)
	if (lastCoinCount != gb::matchCoinCount) {
		if (lastCoinCount < gb::matchCoinCount) {
			animation = true;
			times = glfwGetTime();
		}

		lastCoinCount = gb::matchCoinCount;
		coinCount_text.text = std::to_string(lastCoinCount);
	}

	if (lastScore != gb::matchScore) {
		lastScore = gb::matchScore;
		score_text.text = std::to_string(lastScore);
		score_text.position.x = SCREEN_SIZE_HALF.x - (24 * score_text.text.size());
	}

	// anima o sprite do appleView
	if (animation) {
		float duration = 0.25f;
		float start = 48.f;
		if (diminuir) {
			coin_image.size.x = gb::interpolation(start, 20.f, duration, times);
			coin_image.size.y = gb::interpolation(start, 60.f, duration, times);
			diminuir = !(gb::interpolation(coin_image.size.x, start, duration, times) == 20.f);
		}
		else {
			coin_image.size.x = gb::interpolation(20.f, start, duration, times);
			coin_image.size.y = gb::interpolation(60.f, start, duration, times);
			animation = !(gb::interpolation(coin_image.size.x, start, duration, times) == start);
		}
	}
}

void Hud::draw() {
	coin_image.draw();
	pause_button.draw();
	score_text.draw();
	coinCount_text.draw();
}