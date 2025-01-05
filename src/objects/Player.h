#pragma once

#include "../../Dependencies/glm/glm.hpp"

#include "../GameObject.h"

enum class action : char { JUMP, EMPTY };

class Player : public GameObject {
public:
	Player(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw() override;
	void update() override;

	void input(action action);

	// retorna true o jogador colidiu com algum objeto, senao, false
	bool checkCollision(const GameObject* obj) const;

	float velocity = 0.f;
	float rotate = 0.f;

	// quantidade total de moedas
	unsigned short coinCount = 0;

	//quantidade de moedas por partidas
	unsigned short matchCoinCount = 0;

	// pontua��o do jogador por partida
	unsigned short score = 0;

	//melhor pontua��o do jogador
	unsigned short bestScore = 0;

	// tipo de skin do jogador
	unsigned char skinType = 0;

	bool groundCollided = false;
};