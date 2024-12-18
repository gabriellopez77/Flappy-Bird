#include "Scenery.h"

#include "../global.h"

Scenery::Scenery() {
	background1 = new GameObject(0, 0, 144, 256);
	background1->size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);

	background2 = new GameObject(0, 0, 144, 256);
	background2->size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);
	background2->position = glm::ivec2(background1->position.x + SCREEN_WIDTH, 0);

	ground1 = new GameObject(292, 0, 168, 56);
	ground1->size = glm::ivec2(SCREEN_WIDTH, 168);
	ground1->position = glm::ivec2(0, SCREEN_HEIGHT - 160);

	ground2 = new GameObject(292, 0, 168, 56);
	ground2->size = glm::ivec2(SCREEN_WIDTH, 168);
	ground2->position = glm::ivec2(ground1->position.x + SCREEN_WIDTH, SCREEN_HEIGHT - 160);
}

void Scenery::update() {
	background1->position.x -= BACKGROUND_SPEED * gb::deltaTime;
	background2->position.x -= BACKGROUND_SPEED * gb::deltaTime;

	if (background1->position.x + SCREEN_WIDTH <= 0)
		background1->position.x = background2->position.x + SCREEN_WIDTH;

	else if (background2->position.x + SCREEN_WIDTH <= 0)
		background2->position.x = background1->position.x + SCREEN_WIDTH;


	ground1->position.x -= GROUND_SPEED * gb::deltaTime;
	ground2->position.x -= GROUND_SPEED * gb::deltaTime;

	if (ground1->position.x + SCREEN_WIDTH <= 0)
		ground1->position.x = ground2->position.x + SCREEN_WIDTH;

	else if (ground2->position.x + SCREEN_WIDTH <= 0)
		ground2->position.x = ground1->position.x + SCREEN_WIDTH;
}

void Scenery::drawBackground() {
	background1->draw();
	background2->draw();
}

void Scenery::drawGround() {
	ground1->draw();
	ground2->draw();
}