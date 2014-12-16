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
	for (int n = 0; n < fighters; ++n) {
		Text* text = new Text(0, 0, 25, { 0, 0, 0 }, "0%", true);
		damage_texts.push_back(text);
		Text* name_text = new Text(0, 0, 14, { 0, 0, 0 }, "Captain Falcon", true);
		name_texts.push_back(name_text);
	}
	resize_update();
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

void GameUI::resize_update(int w, int h) {
	if (w == 0 && h == 0) {
		w = universe->win_manager->screen_width;
		h = universe->win_manager->screen_height;
	}
	int pos_x = w / (damage_texts.size() + 1);
	int n = 0;
	for (Text* text : damage_texts) {
		text->origin_x = pos_x * (n + 1) + 24;
		text->origin_y = h - 60;
		text->update_alignment();
		++n;
	}
	n = 0;
	pos_x = w / (name_texts.size() + 1);
	for (Text* text : name_texts) {
		text->origin_x = pos_x * (n + 1) - 25;
		text->origin_y = h - 90;
		text->update_alignment();
		++n;
	}
}