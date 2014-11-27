#ifndef DEBUG_UI_H
#define DEBUG_UI_H

#include "../tools/Universal.h"
#include "tools/Text.h"

class DebugUI : Universal {

	public:
		void create();
		void update();
		void remove();
		void update_fps_text(int fps);

	private:
		Text* fps_text;
};

#endif