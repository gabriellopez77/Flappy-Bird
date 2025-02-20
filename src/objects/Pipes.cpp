#include "Pipes.h"

#include "../Global.h"
#include "Player.h"

Pipes Pipes::pipes[3];

Pipes::Pipes() {
	pipeBottom.size = glm::vec2(PIPE_SIZE.x, PIPE_SIZE.y);
	pipeBottom.collision.size = pipeBottom.size;

	pipeTop.size = glm::vec2(PIPE_SIZE.x, PIPE_SIZE.y);
	pipeTop.collision.size = pipeTop.size;

	coin.size = glm::vec2(COIN_SIZE);
	coin.collision.size = coin.size;

	scoreWall.size = glm::vec2(30, PIPE_SPACING.y);
	scoreWall.collision.size = glm::vec2(30.f, PIPE_SPACING.y);
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
		pipeBottom.collision.position.x = pipeBottom.position.x;
		pipeTop.collision.position.x = pipeTop.position.x;
		scoreWall.collision.position.x = scoreWall.position.x;
	}
		
	// logica dos tubos laranja
	if (orange) {
		// inverte o eixo Y dos pipes laranja se chegarem no limite de suas posições
		if (scoreWall.position.y > PIPE_MAX_POS) {
			float distance = scoreWall.position.y - PIPE_MAX_POS;

			pipeBottom.position.y -= distance;
			pipeTop.position.y -= distance;
			coin.position.y -= distance;
			scoreWall.position.y -= distance;
			forceY = -forceY;
		}
		else if (scoreWall.position.y < PIPE_MIN_POS) {
			float distance = PIPE_MIN_POS - scoreWall.position.y;

			pipeBottom.position.y += distance;
			pipeTop.position.y += distance;
			coin.position.y += distance;
			scoreWall.position.y += distance;
			forceY = -forceY;
		}

		float movimentY = forceY * gb::deltaTime;

		// movimenta no eixo Y
		pipeBottom.position.y += movimentY;
		pipeTop.position.y += movimentY;
		scoreWall.position.y += movimentY;

		// atualiza a posição e a hitbox da moeda no eixo Y
		if (!coinCollected) {
			coin.position.y += movimentY;
			coin.collision.position.y = coin.position.y;
		}

		// atualiza as hitbox no eixo Y
		pipeTop.collision.position.y = pipeTop.position.y;
		pipeBottom.collision.position.y = pipeBottom.position.y;
		scoreWall.collision.position.y = scoreWall.position.y;
	}

	// colisoes
	static Player* pl = static_cast<Player*>(gb::player);

	// se a moeda nao tiver sido coletada, verifica se o jogador colidiu com ela
	if (!coinCollected) {
		if (pl->checkCollision(&coin)) {
			coinCollected = true;
		}
	}

	// verifica se o jogador passou pelos pipes
	if (!passed) {
		if (pl->checkCollision(&scoreWall)) {
			gb::matchScore++;
			passed = true;
		}
	}

	// verifica se o jogador se colidiu com algum pipe
	if (pl->checkCollision(&pipeBottom) || pl->checkCollision(&pipeTop)) {
		gb::currentStatus = status::Dead;
	}


	// animação de coleta das moedas
	if (coinCollected && coinVisible) {
		coin.position.x = gb::lerp(coin.position.x, 30.f, 10.f * gb::deltaTime);
		coin.position.y = gb::lerp(coin.position.y, 40.f, 10.f * gb::deltaTime);
		if (coin.position.x <= 40.f && coin.position.y <= 50.f) {
			coinVisible = false;
			gb::matchCoinCount++;
		}
	}
	else coin.position.x -= movimentX;
	coin.collision.position.x = coin.position.x;

	// anima o sprite da moeda se ela estiver visivel
	if (coinVisible)
		coin.setAnimatedSprite(146, 258, 16, 16, 6, 0.2f, gb::deltaTime);
}

void Pipes::resetPipes() {
	for (int i = 0; i < 3; i++) {
		Pipes& p = pipes[i];

		p.coinVisible = true;
		p.coinCollected = false;
		p.passed = false;

		if (p.orange = gb::chance(34)) {
			p.pipeTop.setNormalizedTex(0, 323, 26, 160);
			p.pipeBottom.setNormalizedTex(28, 323, 26, 160);

		if (gb::chance(50))
			p.forceY = -p.forceY;
		}
		else {
			p.pipeTop.setNormalizedTex(56, 323, 26, 160);
			p.pipeBottom.setNormalizedTex(84, 323, 26, 160);
		}

		p.pipeBottom.position.x = SCREEN_SIZE.x + PIPE_SIZE_HALF.y;
		p.pipeBottom.position.y = gb::randNum(PIPE_SPAWN_POS_MIN, PIPE_SPAWN_POS_MAX);
		p.pipeBottom.collision.position = p.pipeBottom.position;

		p.pipeTop.position.x = SCREEN_SIZE.x + PIPE_SIZE_HALF.y;
		p.pipeTop.position.y = (p.pipeBottom.position.y - PIPE_SPACING.y) - PIPE_SIZE.y;
		p.pipeTop.collision.position = p.pipeTop.position;

		p.scoreWall.position.x = p.pipeBottom.position.x + PIPE_SIZE_HALF.x - p.scoreWall.size.x / 2.f;
		p.scoreWall.position.y = p.pipeBottom.position.y - PIPE_SIZE_HALF.y - PIPE_SPACING.y / 2.f;
		p.scoreWall.collision.position = p.scoreWall.position;

		p.coin.position.x = p.pipeBottom.position.x;
		p.coin.position.y = gb::randNum(p.pipeBottom.position.y - PIPE_SIZE_HALF.y - PIPE_SPACING.y + COIN_SIZE /2.f, p.pipeBottom.position.y - PIPE_SIZE_HALF.y - COIN_SIZE / 2.f);
		p.coin.collision.position = p.coin.position;


		p.pipeBottom.position.x += (PIPE_SPACING.x * i +1);
		p.pipeTop.position.x += (PIPE_SPACING.x * i +1);
		p.coin.position.x += (PIPE_SPACING.x * i +1);
		p.scoreWall.position.x += (PIPE_SPACING.x * i + 1);
	}
}

void Pipes::reset() {
	coinVisible = true;
	coinCollected = false;
	passed = false;

	// sorteia se o pipe será ou nao laranja
	if (orange = gb::chance(34)) {
		pipeTop.setNormalizedTex(0, 323, 26, 160);
		pipeBottom.setNormalizedTex(28, 323, 26, 160);

		if (gb::chance(50))
			forceY = -forceY;
	}
	else {
		pipeTop.setNormalizedTex(56, 323, 26, 160);
		pipeBottom.setNormalizedTex(84, 323, 26, 160);
	}

	pipeBottom.position.x = SCREEN_SIZE.x + PIPE_SIZE_HALF.x;
	pipeBottom.position.y = gb::randNum(PIPE_SPAWN_POS_MIN, PIPE_SPAWN_POS_MAX);
	pipeBottom.collision.position = pipeBottom.position;

	pipeTop.position.x = SCREEN_SIZE.x + PIPE_SIZE_HALF.x;
	pipeTop.position.y = (pipeBottom.position.y - PIPE_SPACING.y) - PIPE_SIZE.y;
	pipeTop.collision.position = pipeTop.position;

	coin.position.x = pipeBottom.position.x;
	coin.position.y = gb::randNum(pipeBottom.position.y - PIPE_SIZE_HALF.y - PIPE_SPACING.y + COIN_SIZE / 2.f, pipeBottom.position.y - PIPE_SIZE_HALF.y - COIN_SIZE / 2.f);
	coin.collision.position = coin.position;

	scoreWall.position.x = pipeBottom.position.x + PIPE_SIZE_HALF.x - scoreWall.size.x / 2.f;
	scoreWall.position.y = pipeBottom.position.y - PIPE_SIZE_HALF.y - PIPE_SPACING.y / 2.f;
	scoreWall.collision.position = scoreWall.position;
}

void Pipes::updatePipes() {
	for (int i = 0; i < 3; i++) {
		if (pipes[i].pipeBottom.position.x - pipes[i].pipeBottom.size.x / 2.f + PIPE_SIZE.x < 0.f)
			pipes[i].reset();
		else
			pipes[i].update();
	}
}

void Pipes::drawPipes() {
	for (int i = 0; i <  3; i++)
		pipes[i].draw();
}