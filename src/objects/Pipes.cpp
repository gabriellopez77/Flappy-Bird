#include "Pipes.h"

#include "../Global.h"

Pipes::Pipes() :
	pipeTop(56, 323, 26, 160),
	coin(146, 258, 16, 16),
	pipeBottom(84, 323, 26, 160),
	scoreWall(466, 431, 1, 1)
{
	// sorteia se o pipe será ou nao laranja
	if (orange = gb::chance(34)) {
		pipeTop.setNormalizedTexUV(0, 323, 26, 160);
		pipeBottom.setNormalizedTexUV(28, 323, 26, 160);
		signal = gb::chance(50);
		if (signal)
			veloY = -veloY;
	}

	pipeBottom.collision = new Collision();
	pipeBottom.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeBottom.position = glm::ivec2(SCREEN_WIDTH, gb::randNum(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT));
	pipeBottom.collision->size = pipeBottom.size;
	pipeBottom.collision->position.y = pipeBottom.position.y;

	pipeTop.collision = new Collision();
	pipeTop.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeTop.position.y = (pipeBottom.position.y - PIPE_SPACING) - PIPE_SIZE_Y;
	pipeTop.collision->size = pipeTop.size;
	pipeTop.collision->position.y = pipeTop.position.y;

	coin.collision = new Collision();
	coin.size = glm::ivec2(COIN_SIZE);
	coin.position.x = pipeBottom.position.x + COIN_SIZE;
	coin.position.y = gb::randNum(pipeTop.position.y + PIPE_SIZE_Y, pipeBottom.position.y - COIN_SIZE);
	coin.collision->size = coin.size;
	coin.collision->position.y = coin.position.y;

	scoreWall.collision = new Collision();
	scoreWall.size = glm::vec2(30, PIPE_SPACING);
	scoreWall.position.x = pipeBottom.position.x + pipeBottom.size.x - scoreWall.size.x;
	scoreWall.position.y = pipeBottom.position.y - PIPE_SPACING;
	scoreWall.collision->size = glm::vec2(30.f, PIPE_SPACING);
	scoreWall.collision->position.y = scoreWall.position.y;
}

void Pipes::draw() {
	pipeTop.draw();
	pipeBottom.draw();
	if (coinVisible)
	coin.draw();
}


void Pipes::update() {
	// movimentação dos pipes
	float movimentX = GROUND_SPEED * gb::deltaTime;

	// movimenta os pipes para a esquerda
	pipeBottom.position.x -= movimentX;
	pipeTop.position.x = pipeBottom.position.x;

	// logica dos tubos laranja
	if (orange) {
		float movimentY = veloY * gb::deltaTime;

		// movimenta os pipes no eixo Y
		pipeBottom.position.y += movimentY;
		pipeTop.position.y += movimentY;

		if (!coinCollected) {
			coin.position.y += movimentY;
			coin.collision->position.y = coin.position.y;
		}

		// inverte o eixo Y dos pipes laranja se chegarem no limite de suas posições no eixo Y 
		if (pipeBottom.position.y > PIPE_MAX_HEIGHT) {
			pipeBottom.position.y = PIPE_MAX_HEIGHT;
			veloY = -veloY;
		}
		else if (pipeBottom.position.y < PIPE_MIN_HEIGHT) {
			pipeBottom.position.y = PIPE_MIN_HEIGHT;
			veloY = -veloY;
		}

		// atualiza a posição da hitbox dos pipes no eixo Y
		pipeTop.collision->position.y = pipeTop.position.y;
		pipeBottom.collision->position.y = pipeBottom.position.y;

		//atualiza a posição e a hitbox do scoreWall no eixo Y
		scoreWall.position.y = pipeBottom.position.y - PIPE_SPACING;
		scoreWall.collision->position.y = scoreWall.position.y;
	}

	// atualiza a posição da hitbox dos pipes no eixo X
	pipeBottom.collision->position.x = pipeBottom.position.x;
	pipeTop.collision->position.x = pipeTop.position.x;

	//atualiza a posição e a hitbox do scoreWall no eixo X
	scoreWall.position.x -= movimentX;
	scoreWall.collision->position.x = scoreWall.position.x;


	// animação de coleta das moedas
	if (coinCollected && coinVisible) {
		coin.position.x = gb::lerp(coin.position.x, 30.f, 10.f * gb::deltaTime);
		coin.position.y = gb::lerp(coin.position.y, 40.f, 10.f * gb::deltaTime);
		if (coin.position.x <= 40.f && coin.position.y <= 50.f)
			coinVisible = false;
	}
	else coin.position.x -= movimentX;
	coin.collision->position.x = coin.position.x;

	// anima o sprite da moeda se ela estiver visivel
	if (coinVisible)
		coin.setAnimatedSprite(146, 258, 16, 16, 6, 0.2f);
}

void Pipes::updatePipes() {
	for (auto it = gb::pipes.begin(); it != gb::pipes.end(); ) {
		// deleta os pipes se estiverem fora da tela
		if ((*it)->pipeBottom.position.x + PIPE_SIZE_X <= 0.f) {
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