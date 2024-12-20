#include "Pause_screen.h"

#include "../Global.h"

Pause::Pause() {
	id = (int)ui::Pause_screen;
	gb::gui.insert(std::pair<int, InterfaceObject*>(id, this));
}

void Pause::update() {

}

void Pause::draw() {

}