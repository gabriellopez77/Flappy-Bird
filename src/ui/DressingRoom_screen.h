#pragma once

#include "../../Dependencies/ml/Sprite.h"

#include "../InterfaceObject.h"
#include "../objects/Button.h"
#include "../objects/Text.h"

#include <array>

class DressingRoom : public InterfaceObject {
public:
	DressingRoom();

	struct Item {
		Item() :
			itemPrice_text(138, 323, 6, 7, 10),
			position(0.f) {

			buyItem_button.setNormalizedTex(349, 498, 37, 14);
			coin_image.setNormalizedTex(194, 258, 16, 16);
		}
		glm::vec2 position;

		ml::Sprite birdSkin_image;
		Button buyItem_button;
		ml::Sprite coin_image;
		Text itemPrice_text;
		unsigned short price = 0;
		unsigned char skinType = 0;
		bool purchased = false;

		void draw() {
			birdSkin_image.draw();
			buyItem_button.draw();
			if (!purchased) {
				coin_image.draw();
				itemPrice_text.draw();
			}
		}
	};

	void update() override;
	void draw() override;
	void start() override;

	std::array<Item, 3> item_list;

	ml::Sprite coinCount_image;
	Text coinCount_text;
	ml::Sprite panel_image;
	ml::Sprite selectedItem_image;
	Button close_button;
	Item* currentSelected = nullptr;
};