#include "Scenery.h"

#include "../global.h"
#include "Player.h"

#include <iostream>
Scenery::Scenery() :
	background1(0, 0, 144, 256),
	background2(0, 0, 144, 256),
	ground1(292, 0, 168, 56),
	ground2(292, 0, 168, 56)
{
	background1.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);

	background2.size = glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT - 50);
	background2.position = glm::ivec2(background1.position.x + SCREEN_WIDTH -5, 0);

	ground1.collision = new Collision();
	ground1.size = glm::ivec2(SCREEN_WIDTH, 168);
	ground1.position = glm::ivec2(0, SCREEN_HEIGHT - 160);
	ground1.collision->size = glm::vec2(ground1.size.x, ground1.size.y);
	ground1.collision->position.y = ground1.position.y;

	ground2.collision = new Collision();
	ground2.size = glm::ivec2(SCREEN_WIDTH, 168);
	ground2.position = glm::ivec2(ground1.position.x + SCREEN_WIDTH, SCREEN_HEIGHT - 160);
	ground2.collision->size = glm::vec2(ground2.size.x, ground2.size.y);
	ground2.collision->position.y = ground2.position.y;
}

void Scenery::update() {
	// verifica se o jogador bateu no chao
	Player* pl = ((Player*)gb::player);
	if (pl->checkCollision(&ground1) || pl->checkCollision(&ground2)) {
		pl->groundCollided = true;
		pl->velocity = 0;
		pl->position.y = ground1.position.y - pl->collision->size.y - 1;
		pl->collision->position.y = pl->position.y;
		gb::currentStatus = status::Dead;
	}
	if (gb::currentStatus == status::Dead)
		return;

	background1.position.x -= BACKGROUND_SPEED * gb::deltaTime;
	background2.position.x -= BACKGROUND_SPEED * gb::deltaTime;

	if (background1.position.x + SCREEN_WIDTH <= 0)
		background1.position.x = background2.position.x + SCREEN_WIDTH;

	else if (background2.position.x + SCREEN_WIDTH <= 0)
		background2.position.x = background1.position.x + SCREEN_WIDTH;


	ground1.position.x -= GROUND_SPEED * gb::deltaTime;
	ground2.position.x -= GROUND_SPEED * gb::deltaTime;

	if (ground1.position.x + SCREEN_WIDTH <= 0)
		ground1.position.x = ground2.position.x + SCREEN_WIDTH;

	else if (ground2.position.x + SCREEN_WIDTH <= 0)
		ground2.position.x = ground1.position.x + SCREEN_WIDTH;

	ground1.collision->position.x = ground1.position.x;
	ground2.collision->position.x = ground2.position.x;
}

void Scenery::drawBackground() {
	background1.draw();
	background2.draw();
}

void Scenery::drawGround() {
	ground1.draw();
	ground2.draw();
}