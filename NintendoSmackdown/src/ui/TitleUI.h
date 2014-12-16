#ifndef TITLE_UI_H
#define TITLE_UI_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"

class TitleUI : Universal {

	public:
		void create();
		void update();
		void remove();

	private:
		SDL_Rect bg_rect;
		SDL_Rect bg_src_rect;
		Text* enter_text;
};

#endif