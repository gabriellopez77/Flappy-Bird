#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Texture.h"

struct Collision {
	glm::vec2 size = glm::vec2(0.f);
	glm::vec2 position = glm::vec2(0.f);
};

class GameObject {
public:
	/*
	 construtor de objetos com textura
	 spriteX e spriteY: coord X e Y do sprite (supeior esquerdo)
	 spriteWidth e spriteHeight: tamanho X e Y do sprite (em pixels)
	*/
	GameObject(int spriteX, int spriteY, int spriteWidth, int spriteHeight);
	~GameObject();

	// construtor de objetos sem texturas
	GameObject(bool tex);

	// cria o vao e vbo dos objetos
	static void create();

	virtual void draw();
	virtual void update() {}

	// parametros iguais aos do construtor com textura
	void setNormalizedTexUV(int spriteX, int spriteY, int spriteWidth, int spriteHeight);

	/*
	* os 4 primeiros parametros iguais aos do contrutor com textura
	* spritesCount: quantidade de sprites da animação
	* delay: interalo de tempo (em segundos) entre cada sprite
	*/
	void setAnimatedSprite(int spriteX, int spriteY, int spriteWidth, int spriteHeight, int spritesCount, float delay);

	// transforms
	glm::vec2 position =			glm::vec2(0.f);
	glm::ivec2 size =				glm::ivec2(0);

	// colisões
	Collision* collision = nullptr;

	static Texture* texture;
	static Shader* shader;

	float texCoords[8]{ 0.f };
	float alpha = 1.f;

protected:
	float animationDelayTime = 0.f;
	unsigned short animationStage = 0;

	static unsigned int VAO, VBO, EBO, VBO_TEX;
	static const float vertices[8];
	static const unsigned int indices[6];
	static glm::mat4 model;
};