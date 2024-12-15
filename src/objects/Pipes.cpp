#include "Pipes.h"

#include "../Global.h"

#include <iostream>
Pipes::Pipes() :
	pipeBottom(84, 323, 26, 160),
	pipeTop(56, 323, 26, 160),
	coin(146, 258, 16, 16)
{
	pipeBottom.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeTop.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);

	pipeBottom.position = glm::ivec2(SCREEN_WIDTH, gb::randNum(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT));
	pipeTop.position.y = (pipeBottom.position.y - PIPE_SPACING) - PIPE_SIZE_Y;

	coin.size = glm::ivec2(COIN_SIZE);
	coin.position.y = gb::randNum(pipeTop.position.y - PIPE_SIZE_Y, pipeBottom.position.y + COIN_SIZE);

	std::cout << pipeTop.position.y - PIPE_SIZE_Y << '\n';
	std::cout << pipeBottom.position.y + COIN_SIZE << '\n';
}

void Pipes::draw() {
	pipeTop.draw();
	pipeBottom.draw();
	if (coinVisible)
		coin.draw();
}

void Pipes::update() {
	pipeBottom.position.x -= GROUND_SPEED * gb::deltaTime;
	pipeTop.position.x = pipeBottom.position.x;

	coin.position.x = pipeBottom.position.x + COIN_SIZE;
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