#include "Button.h"

#include "../../Dependencies/glfw/glfw3.h"

#include "../Global.h"

Button::Button(
	int spriteX,
	int spriteY,
	int spriteWidth,
	int spriteHeight) :
	GameObject(spriteX, spriteY, spriteWidth, spriteHeight)
{

}
inline void Button::update() {
	hover = checkMouseClick(gb::mousePosX, gb::mousePosY);

	if (hover)
		gb::cursorState = glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);
}

bool Button::checkMouseClick(const double mouseX, const double mouseY) const {
	return	mouseX >= position.x && mouseX <= position.x + size.x &&
			mouseY >= position.y && mouseY <= position.y + size.y;
}