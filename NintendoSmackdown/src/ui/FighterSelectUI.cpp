#include "FighterSelectUI.h"
#include <iostream>
#include <sstream>
#include "../managers/WindowManager.h"
#include "../managers/Assets.h"
#include "../input/InputManager.h"
#include "../managers/StateManager.h"
#include "../renderer/Renderer.h"
#include "../tools/timer/TimerCallback.h"
#include "../GameLoop.h"
#include "MessageBoxManager.h"
#include "../map/Map.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static InputManager* input;
		static StateManager* state;
		static Renderer* renderer;
		static MessageBoxManager* messagebox;
		static TimerCallback* timer;
		static GameLoop* game_loop;
		static Map* map;
};

void FighterSelectUI::create() {
	bg_src_rect.x = 0; bg_src_rect.y = 0; bg_src_rect.w = 1920; bg_src_rect.h = 1080;

	start_button = new Button(0, 0, "Start", [this](void) {
		universe->map->fighter_types.clear();
		universe->map->player_ids.clear();
		for (int n = 0; n < selectors.size(); ++n) {
			selectors[n].selected = false;
		}

		int rows = 10;
		int columns = 5;
		int width = rows * 64;
		for (int y = 0; y < columns; ++y) {
			for (int x = 0; x < rows; ++x) {
				rect.x = (universe->win_manager->center_x - (width / 2)) + (x * 64);
				rect.y = 80 + (y * 64);

				if ((x == 0 && y == 0) || (x == 1 && y == 0)) {
					for (int n = 0; n < selectors.size(); ++n) {
						if (!selectors[n].selected) {
							if (selectors[n].rect.x > rect.x - 64 && selectors[n].rect.x < rect.x + 64 &&
								selectors[n].rect.y > rect.y - 64 && selectors[n].rect.y < rect.y + 64) {
								universe->map->fighter_types.push_back(x);
								universe->map->player_ids.push_back(selectors[n].input_id);
								selectors[n].selected = true;
							}
						}
					}
				}
			}
		}

		if (selectors.size() != 0 && universe->map->fighter_types.size() == selectors.size()) {
			universe->state->switch_state(GAME);
		}
	}, 192, 64, 15, { 120, 0, 0 });
	back_button = new Button(0, 0, "Back", [this](void) {
		universe->state->switch_state(MAIN_MENU);
	}, 192, 64, 15, { 120, 0, 0 });

	created = true;

	resize_update();
	std::cout << "options ui initiated\n";
}

void FighterSelectUI::update() {
	universe->renderer->render(universe->assets->options_background, &bg_src_rect, &bg_rect);

	src_rect.w = 96;
	src_rect.h = 96;
	rect.w = 96;
	rect.h = 96;
	int rows = 10;
	int columns = 5;
	int width = rows * 64;
	for (int y = 0; y < columns; ++y) {
		for (int x = 0; x < rows; ++x) {
			src_rect.x = 192; src_rect.y = 0;
			if (x == 0 && y == 0) { src_rect.x = 0;
			}else if (x == 1 && y == 0) { src_rect.x = 96; }
			rect.x = (universe->win_manager->center_x - (width / 2)) + (x * 64);
			rect.y = 80 + (y * 64);
			universe->renderer->render(universe->assets->fighter_portraits, &src_rect, &rect);
		}
	}

	src_rect.x = 0; src_rect.y = 0; src_rect.w = 32; src_rect.h = 32;
	for (int n = 0; n < selectors.size(); ++n) {
		universe->renderer->render(universe->assets->fighter_selector, &src_rect, &selectors[n].rect);
	}

	for (int i = 0; i < universe->input->INPUTS; ++i) {
		Selector* selector = nullptr;
		for (int n = 0; n < selectors.size(); ++n) {
			if (selectors[n].input_id == i) {
				selector = &selectors[n];
				break;
			}
		}

		if (universe->input->b_key[i]->pressed) {
			universe->state->switch_state(MAIN_MENU);
			return;
		}
		if (selector == nullptr) {
			if (universe->input->a_key[i]->pressed) {
				Selector selector;
				selector.input_id = i;
				selector.rect.x = universe->win_manager->center_x;
				selector.rect.y = universe->win_manager->center_y;
				selector.rect.w = 32;
				selector.rect.h = 32;
				selectors.push_back(selector);
			}
		}else {
			if (universe->input->right_key[i]->down) {
				selector->rect.x += 10;
			}
			if (universe->input->left_key[i]->down) {
				selector->rect.x -= 10;
			}
			if (universe->input->down_key[i]->down) {
				selector->rect.y += 10;
			}
			if (universe->input->up_key[i]->down) {
				selector->rect.y -= 10;
			}
		}
	}

	back_button->render();
	start_button->render();
}

void FighterSelectUI::remove() {
	delete start_button;
	delete back_button;

	selectors.clear();

	created = false;
}

void FighterSelectUI::resize_update(int w, int h) {
	if (w == 0 && h == 0) {
		w = universe->win_manager->screen_width;
		h = universe->win_manager->screen_height;
	}
	bg_rect.w = 1920; bg_rect.h = 1080;
	bg_rect.x = 0; bg_rect.y = 0;
	if (1920 > universe->win_manager->screen_width) {
		bg_rect.x = -(1920 - universe->win_manager->screen_width) / 2;
	}else {
		bg_rect.w = universe->win_manager->screen_width;
	}

	int x = 150; int y = 25;
	int row = 0; int column = 0;

	back_button->set_pos(w - 425, h - 80);
	start_button->set_pos(w - 210, h - 80);
}