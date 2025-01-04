#pragma once

#include "../Dependencies/glm/glm.hpp"

#include "../GameObject.h"

enum class Action : char { JUMP, EMPTY };

class Player : public GameObject {
public:
	Player(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	void draw() override;
	void update() override;

	// 
	void input(Action action);

	// retorna true o jogador colidiu com algum objeto, senao, false
	bool checkCollision(const GameObject* obj) const;

	glm::vec2 velocity = glm::vec2(0.f);

	float rotate = 0.f;

	// quantidade total de moedas
	unsigned short coinCount = 0;

	//quantidade de moedas por partidas
	unsigned short matchCoinCount = 0;

	// pontuação do jogador por partida
	unsigned short score = 0;

	//melhor pontuação do jogador
	unsigned short bestScore = 0;

	// tipo de skin do jogador
	unsigned char skinType = 0;
};