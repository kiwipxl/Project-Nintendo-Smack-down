#ifndef OPTIONS_UI_H
#define OPTIONS_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"
#include "components/Button.h"
#include "components/MessageBox.h"
#include "../tools/timer/Timer.h"
#include "../input/Key.h"

class OptionsUI : Universal {

	public:
		void create();
		void update();
		void remove();

		void resize_update(int w = 0, int h = 0);
		void apply_modifications();

	private:
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;

		DropdownBox* dropdown_res;
		Text* res_text;

		DropdownBox* dropdown_fps;
		Text* fps_text;

		DropdownBox* dropdown_window_mode;
		Text* window_mode_text;

		Button* apply_button;
		Button* back_button;

		vector<Button*> control_buttons;
		vector<Text*> key_texts;
		vector<Key*> mod_keys;
		bool created;

		int mod_screen_width;
		int mod_screen_height;
		int mod_selected_res;
		int mod_selected_fps;
		int mod_fps;
		int mod_selected_window_mode;
		SDL_WindowFlags mod_window_mode;

		int selected_res = 3;
		int selected_fps = 2;
		int selected_window_mode = 1;
		Button* last_clicked_button = nullptr;
		Timer* last_button_timer = nullptr;
		Key* last_key;
};

#endif