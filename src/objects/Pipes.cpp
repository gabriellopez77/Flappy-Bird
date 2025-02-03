#include "Pipes.h"

#include "../Global.h"
#include "Player.h"

Pipes::Pipes() {
	// sorteia se o pipe será ou nao laranja
	if (orange = gb::chance(34)) {
		pipeTop.setNormalizedTex(0, 323, 26, 160);
		pipeBottom.setNormalizedTex(28, 323, 26, 160);
		signal = gb::chance(50);
		if (signal)
			veloY = -veloY;
	}
	else {
		pipeTop.setNormalizedTex(56, 323, 26, 160);
		pipeBottom.setNormalizedTex(84, 323, 26, 160);
	}

	pipeBottom.collision = new Collision();
	pipeBottom.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeBottom.position.x = SCREEN_WIDTH;
	pipeBottom.position.y = gb::randNum(PIPE_MIN_HEIGHT, PIPE_MAX_HEIGHT);
	pipeBottom.collision->size = pipeBottom.size;
	pipeBottom.collision->position.y = pipeBottom.position.y;

	pipeTop.collision = new Collision();
	pipeTop.size = glm::ivec2(PIPE_SIZE_X, PIPE_SIZE_Y);
	pipeTop.position.x = SCREEN_WIDTH;
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
	float movimentX = 0.f;
	 if (gb::currentStatus == status::Started) {
		movimentX = GROUND_SPEED* gb::deltaTime;

		// movimenta para a esquerda
		pipeBottom.position.x -= movimentX;
		pipeTop.position.x -= movimentX;
		scoreWall.position.x -= movimentX;

		// atualiza a posição da hitbox no eixo X
		pipeBottom.collision->position.x = pipeBottom.position.x;
		pipeTop.collision->position.x = pipeTop.position.x;
		scoreWall.collision->position.x = scoreWall.position.x;
	}
		
	// logica dos tubos laranja
	if (orange) {
		// inverte o eixo Y dos pipes laranja se chegarem no limite de suas posições
		if (pipeBottom.position.y > PIPE_MAX_HEIGHT) {
			pipeBottom.position.y = PIPE_MAX_HEIGHT;
			veloY = -veloY;
		}
		else if (pipeBottom.position.y < PIPE_MIN_HEIGHT) {
			pipeBottom.position.y = PIPE_MIN_HEIGHT;
			veloY = -veloY;
		}

		float movimentY = veloY * gb::deltaTime;

		// movimenta os pipes no eixo Y
		pipeBottom.position.y += movimentY;
		pipeTop.position.y += movimentY;

		// atualiza a posição e a hitbox da moeda no eixo Y
		if (!coinCollected) {
			coin.position.y += movimentY;
			coin.collision->position.y = coin.position.y;
		}


		// atualiza a posição no eixo Y
		scoreWall.position.y = pipeBottom.position.y - PIPE_SPACING;

		// atualiza a posição da hitbox no eixo Y
		pipeTop.collision->position.y = pipeTop.position.y;
		pipeBottom.collision->position.y = pipeBottom.position.y;
		scoreWall.collision->position.y = scoreWall.position.y;
	}


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
		coin.setAnimatedSprite(146, 258, 16, 16, 6, 0.2f, gb::deltaTime);


	// colisões

	static Player* pl = static_cast<Player*>(gb::player);

	// se a moeda nao tiver sido coletada, verifica se o jogador colidiu com ela
	if (!coinCollected) {
		if (pl->checkCollision(&coin)) {
			pl->matchCoinCount++;
			coinCollected = true;
		}
	}

	// verifica se o jogador passou pelos pipes
	if (!passed) {
		if (pl->checkCollision(&scoreWall)) {
			pl->score++;
			passed = true;
		}
	}

	// verifica se o jogador se colidiu com algum pipe
	if (pl->checkCollision(&pipeBottom) || pl->checkCollision(&pipeTop)) {
		gb::currentStatus = status::Dead;
	}
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