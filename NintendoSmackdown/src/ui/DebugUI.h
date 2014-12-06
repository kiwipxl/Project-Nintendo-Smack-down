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
		void update_render_info();

	private:
		Text* fps_text;
		Text* render_text;
		Text* transform_render_text;
		Text* vertices_uploaded_text;
		Text* total_renders_text;
};

#endif