#ifndef FIGHTER_SELECT_UI_H
#define FIGHTER_SELECT_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"
#include "components/Button.h"
#include "components/MessageBox.h"
#include "components/Selector.h"
#include "../tools/timer/Timer.h"

class FighterSelectUI : Universal {

	public:
		void create();
		void update();
		void remove();

		void resize_update(int w = 0, int h = 0);

	private:
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;

		SDL_Rect rect;
		SDL_Rect src_rect;

		Button* start_button;
		Button* back_button;

		vector<Selector> selectors;

		bool created;
};

#endif