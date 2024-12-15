#include "Button.h"

#include "../../Dependencies/glfw/glfw3.h"

#include "../Global.h"
#include <iostream>

Button::Button(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight) :
	GameObject(spriteX, spriteY, spriteWidth, spriteHeight)
{

}
void Button::update() {
	checkMouseClick(gb::mousePosX, gb::mousePosY, gb::action);

	if (clicked)
		gb::paused = false;
}

void Button::checkMouseClick(const double mouseX, const double mouseY, const int action) {
	this->clicked = mouseX >= position.x && mouseX <= position.x + size.x &&
					mouseY >= position.y && mouseY <= position.y + size.y &&
					action == GLFW_PRESS;
}