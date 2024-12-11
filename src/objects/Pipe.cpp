#include "Pipe.h"

#include "../global.h"

#include <random>

std::vector<Pipe*> Pipe::pipe_bottom = std::vector<Pipe*>();
std::vector<Pipe*> Pipe::pipe_top = std::vector<Pipe*>();


Pipe::Pipe(char type, int spriteX, int spriteY, int spriteWidth, int spriteHeight) : GameObject(spriteX, spriteY, spriteWidth, spriteHeight) {
	this->type = type;

	if (type) pipe_top.push_back(this);
	else pipe_bottom.push_back(this);
}

void Pipe::updatePipes() {
	for (int i = 0; i < pipe_bottom.size(); i++) {
		if (pipe_bottom[i]->position.x + PIPE_WIDTH <= 0) {
			pipe_bottom[i]->remove = true;
			pipe_top[i]->remove = true;
		}
		pipe_bottom[i]->position.x--;
		pipe_top[i]->position.x = pipe_bottom[i]->position.x;
	}

	for (auto it = pipe_bottom.begin(); it != pipe_bottom.end(); ++it) {
		if ((*it)->remove) {
			delete (*it);
			it = pipe_bottom.erase(it);
		}
	}
	for (auto it = pipe_top.begin(); it != pipe_top.end(); ++it) {
		if ((*it)->remove) {
			delete (*it);
			it = pipe_top.erase(it);
		}
	}
}
void Pipe::drawPipes() {
	for (int i = 0; i < pipe_bottom.size(); i++) {
		pipe_bottom[i]->draw();
		pipe_top[i]->draw();
	}
}
void Pipe::genPipes() {
	std::random_device rd;
	std::mt19937 gen = std::mt19937(rd());
	std::uniform_int_distribution rand_num(200, 450);

	Pipe* bottom = new Pipe(0, 84, 323, 26, 160);
	bottom->size = glm::ivec2(PIPE_WIDTH, PIPE_HEIGHT);
	bottom->position = glm::ivec2(GAME_WIDTH, rand_num(gen));


	Pipe* top = new Pipe(1, 56, 323, 26, 160);
	top->size = glm::ivec2(PIPE_WIDTH, PIPE_HEIGHT);
	top->position = glm::ivec2(bottom->position.x, (bottom->position.y - 160) - PIPE_HEIGHT);
}