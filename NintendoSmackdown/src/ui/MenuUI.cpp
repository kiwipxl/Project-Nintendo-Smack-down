#include "MenuUI.h"
#include <iostream>
#include <sstream>
#include "../managers/WindowManager.h"
#include "../managers/Assets.h"
#include "../input/InputManager.h"
#include "../managers/StateManager.h"
#include "../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static InputManager* input;
		static StateManager* state;
		static Renderer* renderer;
};

void MenuUI::create() {
	box_src_rect.w = 310; box_src_rect.h = 400;
	box_rect.w = 300;
	box_rect.h = 400;
	box_pos = 0;
	box_index = 0;
	bg_src_rect.x = 0; bg_src_rect.y = 0; bg_src_rect.w = 1920; bg_src_rect.h = 1080;

	dropdown_box = new DropdownBox(500, 400);

	resize_update();
	std::cout << "menu ui initiated\n";
}

void MenuUI::update() {
	universe->renderer->render(universe->assets->menu_background, &bg_src_rect, &bg_rect);

	box_pos -= (box_pos - (box_rect.w * box_index)) / 5;
	box_rect.x = (universe->win_manager->screen_width / 2) - (box_rect.w / 2) - box_pos;
	box_rect.y = (universe->win_manager->screen_height / 2) - (box_rect.h / 2) + 100;
	for (int i = 0; i < BOX_AMOUNT; ++i) {
		box_rect.x += 4;
		box_src_rect.x = box_src_rect.w * 4;
		if (i == box_index) { box_src_rect.x += box_src_rect.w; }
		universe->renderer->render(universe->assets->menu_boxes_sheet, &box_src_rect, &box_rect);
		box_rect.x -= 4;
		box_src_rect.x = box_src_rect.w * i;
		box_src_rect.y = 0;
		universe->renderer->render(universe->assets->menu_boxes_sheet, &box_src_rect, &box_rect);
		box_rect.x += box_rect.w;
	}

	for (int i = 0; i < universe->input->INPUTS; ++i) {
		if (universe->input->right_key[i]->pressed) {
			++box_index;
		}else if (universe->input->left_key[i]->pressed) {
			--box_index;
		}
		if (box_index < 0) { box_index = 0; }else if (box_index >= BOX_AMOUNT) { box_index = BOX_AMOUNT - 1; }

		if (universe->input->a_key[i]->pressed) {
			switch (box_index) {
				case 0:
					universe->state->switch_state(GAME);
					break;
			}
		}
	}
}

void MenuUI::remove() {

}

void MenuUI::resize_update(int w, int h) {
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
}