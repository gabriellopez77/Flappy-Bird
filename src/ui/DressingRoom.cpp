#include "DressingRoom.h"

#include "../Global.h"
#include "../objects/Player.h"

#include <iostream>

DressingRoom::DressingRoom() :
	panel_image(235, 455, 113, 57),
	selectedItem_image(292, 198, 7, 7),
	close_button(460, 483, 52, 29),
	coinCount_text(138, 323, 6, 7, 10)
{
	item_list.reserve(3);
	id = (int)ui::DressingRoom_screen;
	gb::gui.insert(std::pair<int, InterfaceObject*>(id, this));

	panel_image.size = glm::ivec2(452, 228);
	panel_image.position = glm::vec2(SCREEN_WIDTH /2 - panel_image.size.x /2, SCREEN_HEIGHT /2 - panel_image.size.y /2);

	close_button.size = glm::ivec2(156, 100);
	close_button.position = glm::vec2(SCREEN_WIDTH /2 - close_button.size.x /2, SCREEN_HEIGHT - 180);

	coinCount_text.size = glm::ivec2(30, 35);
	coinCount_text.position = glm::vec2(400, 220);

	Item* item1 = new Item();
	item1->position = glm::vec2(210, 450);
	item1->birdSkin_image.setNormalizedTexUV(2, 487, 20, 20);
	item1->skinType = 0i8;
	item1->purchased = true;
	item1->itemPrice_text.size = glm::ivec2(24, 28);
	item1->itemPrice_text.position = glm::vec2(item1->position.x + 32 + 5, item1->position.y - 38);
	item1->itemPrice_text.text = std::to_string(item1->price);
	item1->buyItem_button.size = glm::ivec2(111, 42);
	item1->buyItem_button.position = glm::vec2(item1->position.x, item1->position.y);
	item1->birdSkin_image.size = glm::ivec2(PLAYER_SIZE);
	item1->birdSkin_image.position = glm::vec2(item1->buyItem_button.position.x + item1->buyItem_button.size.x /2 - PLAYER_SIZE /2, 350);

	Item* item2 = new Item();
	item2->position = glm::vec2(item1->position.x + 131, item1->position.y);
	item2->birdSkin_image.setNormalizedTexUV(62, 487, 20, 20);
	item2->skinType = 1i8;
	item2->coin_image.size = glm::ivec2(32);
	item2->coin_image.position = glm::vec2(item2->position.x, item2->position.y - 40);
	item2->price = 5;
	item2->itemPrice_text.size = glm::ivec2(24, 28);
	item2->itemPrice_text.position = glm::vec2(item2->position.x + 32 + 5, item2->position.y - 38);
	item2->itemPrice_text.text = std::to_string(item2->price);
	item2->buyItem_button.size = glm::ivec2(111, 42);
	item2->buyItem_button.position = glm::vec2(item2->position.x, item2->position.y);
	item2->buyItem_button.enabled = false;
	item2->buyItem_button.alpha = 0.6f;
	item2->birdSkin_image.size = glm::ivec2(PLAYER_SIZE);
	item2->birdSkin_image.position = glm::vec2(item2->buyItem_button.position.x + item2->buyItem_button.size.x /2 - PLAYER_SIZE /2, 350);
	item2->birdSkin_image.alpha = 0.6f;

	Item* item3 = new Item();
	item3->position = glm::vec2(item2->position.x + 131, item2->position.y);
	item3->birdSkin_image.setNormalizedTexUV(122, 487, 20, 20);
	item3->skinType = 2i8;
	item3->coin_image.size = glm::ivec2(32);
	item3->coin_image.position = glm::vec2(item3->position.x, item3->position.y - 40);
	item3->price = 10;
	item3->itemPrice_text.size = glm::ivec2(24, 28);
	item3->itemPrice_text.position = glm::vec2(item3->position.x + 32 + 5, item3->position.y - 38);
	item3->itemPrice_text.text = std::to_string(item3->price);
	item3->buyItem_button.size = glm::ivec2(111, 42);
	item3->buyItem_button.position = glm::vec2(item3->position.x, item3->position.y);
	item3->buyItem_button.enabled = false;
	item3->buyItem_button.alpha = 0.6f;
	item3->birdSkin_image.size = glm::ivec2(PLAYER_SIZE);
	item3->birdSkin_image.position = glm::vec2(item3->buyItem_button.position.x + item3->buyItem_button.size.x /2 - PLAYER_SIZE /2, 350);
	item3->birdSkin_image.alpha = 0.6f;

	selectedItem_image.size = glm::vec2(28);

	item_list.push_back(item1);
	item_list.push_back(item2);
	item_list.push_back(item3);

	currentSelected = item_list[((Player*)gb::player)->skinType];
	selectedItem_image.position = glm::ivec2(currentSelected->buyItem_button.position.x + currentSelected->buyItem_button.size.x / 2 - 14, 310);
	currentSelected->buyItem_button.enabled = false;
	currentSelected->buyItem_button.alpha = 0.6f;
	currentSelected->buyItem_button.setNormalizedTexUV(349, 483, 37, 14);
}

void DressingRoom::update() {
	close_button.update();
	item_list[0]->buyItem_button.update();
	item_list[1]->buyItem_button.update();
	item_list[2]->buyItem_button.update();

	coinCount_text.text = std::to_string(((Player*)gb::player)->coinCount);
	

	if (gb::clicked && close_button.hover) gb::currentScreen = (int)ui::Main_screen;

	for (auto obj : item_list) {
		if (!obj->purchased) {
			if (((Player*)gb::player)->coinCount >= obj->price) {
				obj->buyItem_button.enabled = true;
				obj->buyItem_button.alpha = 1.f;
				obj->birdSkin_image.alpha = 1.f;
			}
			else {
				obj->buyItem_button.enabled = false;
				obj->buyItem_button.alpha = 0.6f;
				obj->birdSkin_image.alpha = 0.6f;
			}
		}

		if (gb::clicked && obj->buyItem_button.hover) {
			if (!obj->purchased) {
				((Player*)gb::player)->coinCount -= obj->price;
				obj->purchased = true;
			}

			currentSelected->buyItem_button.enabled = true;
			currentSelected->buyItem_button.alpha = 1.f;
			currentSelected->buyItem_button.setNormalizedTexUV(349, 468, 37, 14);

			obj->buyItem_button.enabled = false;
			obj->buyItem_button.alpha = 0.6f;
			obj->buyItem_button.setNormalizedTexUV(349, 483, 37, 14);
			currentSelected = obj;
			((Player*)gb::player)->skinType = currentSelected->skinType;
			selectedItem_image.position = glm::ivec2(currentSelected->buyItem_button.position.x + currentSelected->buyItem_button.size.x / 2 - 14, 310);
		}
	}
}

void DressingRoom::draw() {
	panel_image.draw();
	close_button.draw();
	coinCount_text.draw();
	selectedItem_image.draw();
	item_list[0]->draw();
	item_list[1]->draw();
	item_list[2]->draw();
}