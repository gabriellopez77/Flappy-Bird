#pragma once

#include "../GameObject.h"

#include "../InterfaceObject.h"
#include "../objects/Button.h"
#include "../objects/Text.h"

#include <vector>

class DressingRoom : public InterfaceObject {
public:
	DressingRoom();

	struct Item {
		Item() :
			birdSkin_image(0, 0, 0, 0),
			buyItem_button(349,498,37,14),
			coin_image(194, 258, 16, 16),
			//itemPrice_text(138, 323, 6, 7, 10),
			position(0.f)
		{
		}
		glm::vec2 position;

		GameObject birdSkin_image;
		Button buyItem_button;
		GameObject coin_image;
		//Text itemPrice_text;

		void draw() {
			birdSkin_image.draw();
			buyItem_button.draw();
			coin_image.draw();
			//itemPrice_text.draw();
		}
	};

	void update() override;
	void draw() override;

	std::vector<Item*> item_list;

	Text coinCount_text;
	GameObject panel_image;
	GameObject selectedItem_image;
	Button close_button;
	Item* currentSelected = nullptr;
};