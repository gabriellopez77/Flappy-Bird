#include "Scenery.h"

#include "../global.h"
#include "Player.h"

Scenery::Scenery() {
	background1.size = glm::vec2(SCREEN_SIZE.x, SCREEN_SIZE.y);
	background1.position =  glm::vec2(SCREEN_SIZE_HALF.x, SCREEN_SIZE_HALF.y);
	background1.setNormalizedTex(0, 0, 144, 256);

	background2.size = glm::vec2(SCREEN_SIZE.x, SCREEN_SIZE.x);
	background2.position = glm::vec2(background1.position.x + SCREEN_SIZE.x, SCREEN_SIZE_HALF.y);
	background2.setNormalizedTex(0, 0, 144, 256);

	ground1.size = GROUND_SIZE;
	ground1.position = glm::vec2(SCREEN_SIZE_HALF.y, SCREEN_SIZE.y - ground1.size.y / 2.f);
	ground1.collision.size = GROUND_SIZE;
	ground1.collision.position.y = ground1.position.y;
	ground1.setNormalizedTex(292, 0, 168, 56);

	ground2.size = GROUND_SIZE;
	ground2.position = glm::vec2(ground1.position.x + SCREEN_SIZE.x, ground1.position.y);
	ground2.collision.size = GROUND_SIZE;
	ground2.collision.position.y = ground2.position.y;
	ground2.setNormalizedTex(292, 0, 168, 56);
}

void Scenery::update() {
	// verifica se o jogador bateu no chao
	Player* pl = ((Player*)gb::player);
	if (pl->checkCollision(&ground1) || pl->checkCollision(&ground2)) {
		pl->groundCollided = true;
		pl->velocity = 0;
		pl->position.y = ground1.position.y - ground1.size.y / 2.f - pl->collision.size.y / 2.f - 1;
		pl->collision.position.y = pl->position.y;
		gb::currentStatus = status::Dead;
	}

	if (gb::currentStatus == status::Dead)
		return;

	background1.position.x -= BACKGROUND_SPEED * gb::deltaTime;
	background2.position.x -= BACKGROUND_SPEED * gb::deltaTime;

	if (background1.position.x + SCREEN_SIZE_HALF.x < 0)
		background1.position.x = background2.position.x + SCREEN_SIZE.x;

	else if (background2.position.x + SCREEN_SIZE_HALF.x < 0)
		background2.position.x = background1.position.x + SCREEN_SIZE.x;


	ground1.position.x -= GROUND_SPEED * gb::deltaTime;
	ground2.position.x -= GROUND_SPEED * gb::deltaTime;

	if (ground1.position.x + SCREEN_SIZE_HALF.x < 0)
		ground1.position.x = ground2.position.x + SCREEN_SIZE.x;

	else if (ground2.position.x + SCREEN_SIZE_HALF.x < 0)
		ground2.position.x = ground1.position.x + SCREEN_SIZE.x;

	ground1.collision.position.x = ground1.position.x;
	ground2.collision.position.x = ground2.position.x;
}

void Scenery::drawBackground() {
	background1.draw();
	background2.draw();
}

void Scenery::drawGround() {
	ground1.draw();
	ground2.draw();
}