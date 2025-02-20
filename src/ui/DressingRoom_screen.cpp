#include "DressingRoom_screen.h"

#include "../Global.h"
#include "../objects/Player.h"

DressingRoom::DressingRoom() :
	coinCount_text(138, 323, 6, 7, 10)
{
	id = ui::DressingRoom_screen;
	gb::gui.insert(std::pair<ui, InterfaceObject*>(id, this));

	panel_image.size = glm::vec2(452, 228);
	panel_image.position = glm::vec2(SCREEN_SIZE_HALF.x, SCREEN_SIZE_HALF.y);
	panel_image.setNormalizedTex(235, 455, 113, 57);

	float panelX = panel_image.position.x;
	float panelY = panel_image.position.y;

	coinCount_image.size = glm::vec2(64);
	coinCount_image.position = glm::vec2(panelX, panelY - 180.f);
	coinCount_image.setNormalizedTex(194, 258, 16, 16);

	coinCount_text.size = glm::vec2(30, 35);
	coinCount_text.position = glm::vec2(coinCount_image.position.x + coinCount_image.size.x + 20, coinCount_image.position.y);

	close_button.size = glm::vec2(156, 100);
	close_button.position = glm::vec2(SCREEN_SIZE_HALF.x, SCREEN_SIZE.y - 180);
	close_button.setNormalizedTex(460, 483, 52, 29);


	Item& item1 = item_list[0];
	item1.position = glm::vec2(panelX - 125.f, panelY + 70.f);
	item1.birdSkin_image.setNormalizedTex(2, 487, 20, 20);
	item1.purchased = true;

	item1.itemPrice_text.size = glm::vec2(24, 28);
	item1.itemPrice_text.position = glm::vec2(item1.position.x - 25.f, item1.position.y - 40.f);
	item1.itemPrice_text.text = std::to_string(item1.price);

	item1.buyItem_button.size = glm::vec2(111, 42);
	item1.buyItem_button.position = glm::vec2(item1.position.x, item1.position.y);

	item1.birdSkin_image.size = glm::vec2(PLAYER_SIZE);	
	item1.birdSkin_image.position = glm::vec2(item1.position.x, item1.position.y - 100);


	Item& item2 = item_list[1];
	item2.position = glm::vec2(item1.position.x + 131, item1.position.y);
	item2.birdSkin_image.setNormalizedTex(62, 487, 20, 20);
	item2.skinType = 1;
	item2.price = 50;

	item2.coin_image.size = glm::vec2(32);
	item2.coin_image.position = glm::vec2(item2.position.x - 40.f, item1.position.y - 40.f);

	item2.itemPrice_text.size = glm::vec2(24, 28);
	item2.itemPrice_text.position = glm::vec2(item2.position.x, item2.coin_image.position.y);
	item2.itemPrice_text.text = std::to_string(item2.price);

	item2.buyItem_button.size = glm::vec2(111, 42);
	item2.buyItem_button.position = glm::vec2(item2.position.x, item2.position.y);
	item2.buyItem_button.enabled = false;
	item2.buyItem_button.alpha = 0.6f;

	item2.birdSkin_image.size = glm::vec2(PLAYER_SIZE);
	item2.birdSkin_image.position = glm::vec2(item2.position.x, item2.position.y - 100);
	item2.birdSkin_image.alpha = 0.6f;


	Item& item3 = item_list[2];
	item3.position = glm::vec2(item2.position.x + 131, item2.position.y);
	item3.birdSkin_image.setNormalizedTex(122, 487, 20, 20);
	item3.skinType = 2;
	item3.price = 100;

	item3.coin_image.size = glm::vec2(32);
	item3.coin_image.position = glm::vec2(item3.position.x - 40.f, item2.coin_image.position.y);

	item3.itemPrice_text.size = glm::vec2(24, 28);
	item3.itemPrice_text.position = glm::vec2(item3.position.x, item2.coin_image.position.y);
	item3.itemPrice_text.text = std::to_string(item3.price);

	item3.buyItem_button.size = glm::vec2(111, 42);
	item3.buyItem_button.position = glm::vec2(item3.position.x, item1.position.y);
	item3.buyItem_button.enabled = false;
	item3.buyItem_button.alpha = 0.6f;

	item3.birdSkin_image.size = glm::vec2(PLAYER_SIZE);
	item3.birdSkin_image.position = glm::vec2(item3.position.x, item1.position.y - 100);
	item3.birdSkin_image.alpha = 0.6f;



	selectedItem_image.size = glm::vec2(28);
	selectedItem_image.setNormalizedTex(292, 198, 7, 7);

	currentSelected = &item_list[((Player*)gb::player)->skinType];
	selectedItem_image.position = glm::vec2(currentSelected->birdSkin_image.position.x, 310);
	currentSelected->buyItem_button.enabled = false;
	currentSelected->buyItem_button.alpha = 0.6f;
	currentSelected->buyItem_button.setNormalizedTex(349, 483, 37, 14);
}

void DressingRoom::start() {
	coinCount_text.text = std::to_string(((Player*)gb::player)->coinCount);
}

void DressingRoom::update() {
	close_button.update();
	item_list[0].buyItem_button.update();
	item_list[1].buyItem_button.update();
	item_list[2].buyItem_button.update();

	// botao de fechar
	if (gb::clicked && close_button.hover)
		gb::changeCurrentInterface(ui::Main_screen);


	static Player* pl = static_cast<Player*>(gb::player);

	for (auto& obj : item_list) {
		if (!obj.purchased && pl->coinCount >= obj.price) {
			obj.buyItem_button.enabled = true;
			obj.buyItem_button.alpha = 1.f;
			obj.birdSkin_image.alpha = 1.f;
		}

		if (gb::clicked && obj.buyItem_button.hover) {

			// compra o item
			if (!obj.purchased) {
				pl->coinCount -= obj.price;
				obj.purchased = true;
			}

			// muda o estado do item clicado para desabilitado
			obj.buyItem_button.enabled = false;
			obj.buyItem_button.alpha = 0.6f;
			// muda a textura do botao para "equiped"
			obj.buyItem_button.setNormalizedTex(349, 483, 37, 14);


			// muda o estado do item atualmente selecionado pra habilitado
			currentSelected->buyItem_button.enabled = true;
			currentSelected->buyItem_button.alpha = 1.f;
			// muda a textura do botao para "equipd"
			currentSelected->buyItem_button.setNormalizedTex(349, 468, 37, 14);

			// troca o atual item selecionado
			currentSelected = &obj;


			// muda a skin do jogador
			pl->skinType = currentSelected->skinType;

			// muda a posicao do icone verde
			selectedItem_image.position.x = currentSelected->birdSkin_image.position.x;
		}
	}
}

void DressingRoom::draw() {
	panel_image.draw();
	close_button.draw();
	coinCount_text.draw();
	coinCount_image.draw();
	selectedItem_image.draw();
	item_list[0].draw();
	item_list[1].draw();
	item_list[2].draw();
}