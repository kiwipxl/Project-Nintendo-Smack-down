#include "OptionsUI.h"
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
};

void OptionsUI::create() {
	bg_src_rect.x = 0; bg_src_rect.y = 0; bg_src_rect.w = 1920; bg_src_rect.h = 1080;

	mod_screen_width = universe->win_manager->screen_width;
	mod_screen_height = universe->win_manager->screen_height;
	mod_selected_res = selected_res;
	mod_selected_window_mode = selected_window_mode;
	mod_window_mode = universe->win_manager->window_flags;
	mod_selected_fps = selected_fps;
	mod_fps = universe->game_loop->get_fps();

	res_text = new Text(0, 0, 15, { 255, 255, 255 }, "Screen resolution: ", true);

	dropdown_res = new DropdownBox(0, 0);
	dropdown_res->add_box("640x400", [this](void) { 
		mod_screen_width = 640; mod_screen_height = 400; mod_selected_res = 1; });
	dropdown_res->add_box("1024x640", [this](void) { 
		mod_screen_width = 1024; mod_screen_height = 640; mod_selected_res = 2; });
	dropdown_res->add_box("1080x768", [this](void) { 
		mod_screen_width = 1080; mod_screen_height = 768; mod_selected_res = 3; });
	dropdown_res->add_box("1280x720", [this](void) { 
		mod_screen_width = 1280; mod_screen_height = 720; mod_selected_res = 4; });
	dropdown_res->add_box("1280x800", [this](void) { 
		mod_screen_width = 1280; mod_screen_height = 800; mod_selected_res = 5; });
	dropdown_res->add_box("1440x900", [this](void) {
		mod_screen_width = 1440; mod_screen_height = 900; mod_selected_res = 6; });
	dropdown_res->add_box("1600x1200", [this](void) { 
		mod_screen_width = 1600; mod_screen_height = 1200; mod_selected_res = 7; });
	dropdown_res->add_box("1920x1080", [this](void) { 
		mod_screen_width = 1920; mod_screen_height = 1080; mod_selected_res = 8; });
	dropdown_res->add_box("1920x1200", [this](void) { 
		mod_screen_width = 1920; mod_screen_height = 1200; mod_selected_res = 9; });
	dropdown_res->add_box("1920x1440", [this](void) { 
		mod_screen_width = 1920; mod_screen_height = 1440; mod_selected_res = 10; });
	dropdown_res->add_box("2560x1080", [this](void) { 
		mod_screen_width = 2560; mod_screen_height = 1080; mod_selected_res = 11; });
	dropdown_res->add_box("2560x1920", [this](void) { 
		mod_screen_width = 2560; mod_screen_height = 1920; mod_selected_res = 12; });
	dropdown_res->select(selected_res);

	window_mode_text = new Text(0, 0, 15, { 255, 255, 255 }, "Window mode: ", true);

	dropdown_window_mode = new DropdownBox(0, 0);
	dropdown_window_mode->add_box("Windowed", [this](void) { 
		mod_selected_window_mode = 1; mod_window_mode = SDL_WINDOW_SHOWN; });
	dropdown_window_mode->add_box("Borderless", [this](void) { 
		mod_selected_window_mode = 2; mod_window_mode = SDL_WINDOW_BORDERLESS; });
	dropdown_window_mode->add_box("Fullscreen", [this](void) { 
		mod_selected_window_mode = 3; mod_window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP; });
	dropdown_window_mode->add_box("Resizable", [this](void) { 
		mod_selected_window_mode = 4; mod_window_mode = SDL_WINDOW_RESIZABLE; });
	dropdown_window_mode->select(selected_window_mode);

	fps_text = new Text(0, 0, 15, { 255, 255, 255 }, "Fps: ", true);

	dropdown_fps = new DropdownBox(0, 0);
	dropdown_fps->add_box("30", [this](void) { mod_selected_fps = 1; mod_fps = 30; });
	dropdown_fps->add_box("60", [this](void) { mod_selected_fps = 2; mod_fps = 60; });
	dropdown_fps->add_box("90", [this](void) { mod_selected_fps = 3; mod_fps = 90; });
	dropdown_fps->add_box("120", [this](void) { mod_selected_fps = 4; mod_fps = 120; });
	dropdown_fps->select(selected_fps);

	apply_button = new Button(0, 0, "Apply changes", [this](void) {
		universe->messagebox->show(new MessageBox(0, 0, "Save changes",
			"Are you sure you want to apply any new changes?", 15), NO_YES);
		universe->messagebox->change_press_function(0, [this](void) {
			apply_modifications();
		});
	}, 192, 64, 15, { 120, 0, 0 });
	back_button = new Button(0, 0, "Back", [this](void) {
		universe->state->switch_state(MAIN_MENU);
	}, 192, 64, 15, { 120, 0, 0 });

	last_clicked_button = nullptr;
	last_button_timer = nullptr;
	for (int i = 0; i < universe->input->INPUTS; ++i) {
		for (int n = 0; n < universe->input->KEYS; ++n) {
			Key* key = universe->input->allkeys[n][i];
			std::string name = universe->input->get_name(key);

			Key* mod_key = new Key();
			mod_key->set_key(key->key, key->type);
			mod_keys.push_back(mod_key);

			Button* button = new Button(0, 0, name, nullptr, 140, 40, 14, { 120, 0, 0 });
			button->press_function = [this, button, mod_key](void) {
				button->text->render_text("<press a key>", true);
				if (last_clicked_button != nullptr) {
					last_clicked_button->text->render_text(universe->input->get_name(last_key), true);
					last_button_timer->end();
					last_button_timer = nullptr;
				}
				last_clicked_button = button;
				last_key = mod_key;
				last_button_timer = universe->timer->set_timer([this, button, mod_key](void) {
					button->text->render_text(universe->input->get_name(mod_key), true);
					last_clicked_button = nullptr;
				}, 2500);
			};
			control_buttons.push_back(button);
		}
	}

	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "Right key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "Left key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "Up key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "Down key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "A key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "B key: ", true));
	key_texts.push_back(new Text(0, 0, 15, { 255, 255, 255 }, "D key: ", true));

	created = true;

	resize_update();
	std::cout << "options ui initiated\n";
}

void OptionsUI::apply_modifications() {
	universe->win_manager->resize(mod_screen_width, mod_screen_height);
	universe->messagebox->hide();
	selected_res = mod_selected_res;
	selected_window_mode = mod_selected_window_mode;
	selected_fps = mod_selected_fps;
	universe->game_loop->set_fps(mod_fps);
	cout << mod_window_mode << "\n";
	universe->win_manager->set_window_flags(mod_window_mode);

	int m = 0;
	for (int i = 0; i < universe->input->INPUTS; ++i) {
		for (int n = 0; n < universe->input->KEYS; ++n) {
			universe->input->allkeys[n][i]->set_key(mod_keys[m]->key, mod_keys[m]->type);
			++m;
		}
	}
}

void OptionsUI::update() {
	universe->renderer->render(universe->assets->options_background, &bg_src_rect, &bg_rect);

	fps_text->render();
	dropdown_fps->render();
	window_mode_text->render();
	dropdown_window_mode->render();
	res_text->render();
	dropdown_res->render();
	apply_button->render();

	for (Button* button : control_buttons) {
		button->render();
	}

	for (Text* key_text : key_texts) {
		key_text->render();
	}

	if (last_clicked_button != nullptr) {
		if (universe->input->last_key->pressed) {
			last_key->set_key(universe->input->last_key->key, universe->input->last_key->type);
			last_clicked_button->text->render_text(universe->input->get_name(last_key), true);

			last_button_timer->end();
			last_button_timer = nullptr;
			last_clicked_button = nullptr;
		}
	}else {
		for (int i = 0; i < universe->input->INPUTS; ++i) {
			if (universe->input->b_key[i]->pressed) {
				universe->state->switch_state(MAIN_MENU);
				break;
			}
		}
	}

	back_button->render();
}

void OptionsUI::remove() {
	delete res_text;
	delete dropdown_res;
	delete window_mode_text;
	delete dropdown_window_mode;
	delete fps_text;
	delete dropdown_fps;
	delete apply_button;
	delete back_button;

	for (Button* &button : control_buttons) {
		delete button;
	}
	control_buttons.clear();

	for (int n = 0; n < mod_keys.size(); ++n) {
		delete mod_keys[n];
	}
	mod_keys.clear();

	if (last_button_timer != nullptr) { last_button_timer->end(); }

	for (Text* key_text : key_texts) {
		delete key_text;
	}
	key_texts.clear();

	created = false;
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

	int x = 150; int y = 25;
	int row = 0; int column = 0;

	back_button->set_pos(w - 425, h - 80);
	apply_button->set_pos(w - 210, h - 80);

	dropdown_res->set_pos(x + 80, 380);
	res_text->origin_x = x - 120;
	res_text->origin_y = 385;
	res_text->update_alignment();

	dropdown_window_mode->set_pos(x + 80, 450);
	window_mode_text->origin_x = x - 120;
	window_mode_text->origin_y = 455;
	window_mode_text->update_alignment();

	dropdown_fps->set_pos(x + 80, 520);
	fps_text->origin_x = x - 120;
	fps_text->origin_y = 525;
	fps_text->update_alignment();

	for (Button* button : control_buttons) {
		button->set_pos(x + (row * 150), y + (column * 48));
		++column;
		if (column >= universe->input->KEYS) {
			column = 0;
			++row;
		}
	}

	int index = 0;
	for (Text* key_text : key_texts) {
		key_text->origin_x = x - 120;
		key_text->origin_y = y + 8 + (index * 48);
		key_text->update_alignment();
		++index;
	}
}