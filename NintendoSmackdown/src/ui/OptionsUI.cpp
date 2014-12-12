#include "OptionsUI.h"
#include <iostream>
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

void OptionsUI::create() {
	bg_src_rect.x = 0; bg_src_rect.y = 0; bg_src_rect.w = 1920; bg_src_rect.h = 1080;

	dropdown_box = new DropdownBox(universe->win_manager->center_x, universe->win_manager->center_y);
	dropdown_box->add_box("640x400", [this](void) { universe->win_manager->resize(640, 400); });
	dropdown_box->add_box("1024x640", [this](void) { universe->win_manager->resize(1024, 640); });
	dropdown_box->add_box("1080x768", [this](void) { universe->win_manager->resize(1080, 768); });
	dropdown_box->add_box("1280x720", [this](void) { universe->win_manager->resize(1280, 720); });
	dropdown_box->add_box("1280x800", [this](void) { universe->win_manager->resize(1280, 800); });
	dropdown_box->add_box("1440x900", [this](void) { universe->win_manager->resize(1440, 900); });
	dropdown_box->add_box("1600x1200", [this](void) { universe->win_manager->resize(1600, 1200); });
	dropdown_box->add_box("1920x1080", [this](void) { universe->win_manager->resize(1920, 1080); });
	dropdown_box->add_box("1920x1200", [this](void) { universe->win_manager->resize(1920, 1200); });
	dropdown_box->add_box("1920x1440", [this](void) { universe->win_manager->resize(1920, 1440); });
	dropdown_box->add_box("2560x1080", [this](void) { universe->win_manager->resize(2560, 1080); });
	dropdown_box->add_box("2560x1920", [this](void) { universe->win_manager->resize(2560, 1920); });
	dropdown_box->select(3);

	resize_update();
	std::cout << "menu ui initiated\n";
}

void OptionsUI::update() {
	universe->renderer->render(universe->assets->menu_background, &bg_src_rect, &bg_rect);

	dropdown_box->render();

	for (int i = 0; i < universe->input->INPUTS; ++i) {
		if (universe->input->b_key[i]->pressed) {
			universe->state->switch_state(MAIN_MENU);
			break;
		}
	}
}

void OptionsUI::remove() {

}

void OptionsUI::resize_update(int w, int h) {
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