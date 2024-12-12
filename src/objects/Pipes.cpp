#include "Pipes.h"

#include "../global.h"

#include <random>


Pipes::Pipes() :
	pipeTop(56, 323, 26, 160),
	coin(146, 258, 16, 16),
	pipeBottom(84, 323, 26, 160)
{
	std::random_device rd;
	std::mt19937 gen = std::mt19937(rd());
	std::uniform_int_distribution rand_num(200, 450);

	pipeTop.size = glm::ivec2(PIPE_WIDTH, PIPE_HEIGHT);
	pipeBottom.size = glm::ivec2(PIPE_WIDTH, PIPE_HEIGHT);
	coin.size = glm::ivec2(36);

	pipeBottom.position = glm::ivec2(GAME_WIDTH, rand_num(gen));
	pipeTop.position.y = (pipeBottom.position.y - 160) - PIPE_HEIGHT;
}

void Pipes::draw() {
	pipeTop.draw();
	pipeBottom.draw();
	coin.draw();
}

void Pipes::update() {
	pipeBottom.position.x--;
	pipeTop.position.x = pipeBottom.position.x;
	coin.position = glm::ivec2(pipeBottom.position.x + 27, pipeBottom.position.y - 80 - 18);
	coin.setAnimatedSprite(146, 258, 16, 16, 6, 0.2f);
}

void Pipes::updatePipes() {
	for (auto it = gb::pipes.begin(); it != gb::pipes.end(); ) {
		if ((*it)->pipeBottom.position.x + PIPE_WIDTH <= 0) {
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