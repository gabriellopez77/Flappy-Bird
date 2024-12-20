#include "Pipes.h"

#include "../Global.h"

#include <iostream>
Pipes::Pipes() :
	pipeTop(56, 323, 26, 160),
	coin(146, 258, 16, 16),
	pipeBottom(84, 323, 26, 160)
{
	pipeBottom.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeTop.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeTop.collSize = pipeTop.size;

	pipeBottom.position = glm::ivec2(SCREEN_WIDTH, gb::randNum(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT));
	pipeTop.position.y = (pipeBottom.position.y - PIPE_SPACING) - PIPE_SIZE_Y;
	pipeBottom.collSize = pipeBottom.size;

	coin.size = glm::ivec2(COIN_SIZE);
	coin.position.y = gb::randNum(pipeTop.position.y + PIPE_SIZE_Y, pipeBottom.position.y - COIN_SIZE);
	coin.collSize = coin.size;
}

void Pipes::draw() {
	pipeTop.draw();
	pipeBottom.draw();
	if (coinVisible)
	coin.draw();
}

void Pipes::update() {
	// movimentação dos pipes
	pipeBottom.position.x -= GROUND_SPEED * gb::deltaTime;
	pipeTop.position.x = pipeBottom.position.x;
	if (coinCollected && coinVisible) {
		coin.position.x = gb::lerp(coin.position.x, 30, 20.f * gb::deltaTime);
		coin.position.y = gb::lerp(coin.position.y, 40, 20.f * gb::deltaTime);
		if (coin.position.x <=  40 && coin.position.y <= 50)
			coinVisible = false;
	}
	else coin.position.x = pipeBottom.position.x + COIN_SIZE;

	pipeBottom.collPosition = pipeBottom.position;
	pipeTop.collPosition = pipeTop.position;
	coin.collPosition = coin.position;

	coin.setAnimatedSprite(146, 258, 16, 16, 6, 0.2f);
}

void Pipes::updatePipes() {
	for (auto it = gb::pipes.begin(); it != gb::pipes.end(); ) {
		if ((*it)->pipeBottom.position.x + PIPE_SIZE_X <= 0) {
			delete (*it);
			it = gb::pipes.erase(it);
		}
		else {
			(*it)->update();
			++it;
		}
	}
}

void Pipes::drawPipes() {
	for (Pipes* pipes : gb::pipes)
		pipes->draw();
}