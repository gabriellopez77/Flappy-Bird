#pragma once

#include "GameObject.h"

#include <vector>

class Pipe : public GameObject {
public:
	Pipe(char type, int spriteX, int spriteY, int spriteWidth, int spriteHeight);
	char type;

	static std::vector<Pipe*> pipe_bottom;
	static std::vector<Pipe*> pipe_top;

	static void updatePipes();
	static void drawPipes();
	static void genPipes();	
};