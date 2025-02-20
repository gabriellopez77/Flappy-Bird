#include "Button.h"

#include "../../Dependencies/glfw/glfw3.h"

#include "../Global.h"

void Button::update() {
	if (enabled)
		hover = checkMouseClick(gb::mousePosX, gb::mousePosY);
	else
		hover = false;

	if (hover) gb::cursorState = glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);
}

bool Button::checkMouseClick(float mouseX, float mouseY) const {
	return	mouseX >= position.x - size.x / 2.f && mouseX <= position.x + size.x / 2.f &&
			mouseY >= position.y - size.y / 2.f && mouseY <= position.y + size.y / 2.f;
}