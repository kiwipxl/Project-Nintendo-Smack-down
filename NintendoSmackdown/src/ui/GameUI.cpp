#include "GameUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../managers/WindowManager.h"
#include "../GameLoop.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static GameLoop* game_loop;
};

void GameUI::create() {
	std::cout << "game_ui initiated\n";
}

void GameUI::create_damage_texts(int fighters) {
	int pos_x = universe->win_manager->screen_width / (fighters + 1);
	for (int n = 0; n < fighters; ++n) {
		Text* text = new Text(pos_x * (n + 1), universe->win_manager->screen_height - 60, 
		35, { 0, 0, 0 }, "0%", true);
		damage_texts.push_back(text);
		Text* name_text = new Text(pos_x * (n + 1) - 25, universe->win_manager->screen_height - 90, 
		18, { 0, 0, 0 }, "Captain Falcon", true);
		name_texts.push_back(name_text);
	}
}

void GameUI::update() {
	for (Text* text : damage_texts) {
		text->render();
	}
	for (Text* text : name_texts) {
		text->render();
	}
}

void GameUI::update_damage_text(int index, int damage) {
	std::string damagestr = std::to_string(damage) + "%";
	damage_texts[index]->render_text(damagestr, true);
}

void GameUI::remove() {
	for (Text* text : damage_texts) {
		delete text;
	}
	damage_texts.clear();
	for (Text* text : name_texts) {
		delete text;
	}
	name_texts.clear();
}