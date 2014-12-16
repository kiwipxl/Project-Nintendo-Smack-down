#include "TitleUI.h"
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

void TitleUI::create() {
	bg_rect.x = 0; bg_rect.y = 0;
	bg_rect.w = universe->win_manager->screen_width;
	bg_rect.h = universe->win_manager->screen_height;
	bg_src_rect.x = 0; bg_src_rect.y = 0; bg_src_rect.w = 1024; bg_src_rect.h = 768;

	std::cout << "title ui initiated\n";
}

void TitleUI::update() {
	universe->renderer->render(universe->assets->title_background, &bg_src_rect, &bg_rect);

	for (int i = 0; i < universe->input->INPUTS; ++i){
		if (universe->input->a_key[i]->pressed) {
			universe->state->switch_state(MAIN_MENU);
		}
	}
	enter_text = new Text(0, 10, 50, { 0, 0, 0 }, "Press Any Key To Continue", true);
	enter_text->rect.x = (universe->win_manager->screen_width / 2) - (enter_text->rect.w / 2);
	enter_text->render();
}

void TitleUI::remove() {

}