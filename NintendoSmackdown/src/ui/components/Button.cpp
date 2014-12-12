#include "Button.h"
#include <sstream>
#include "../../managers/WindowManager.h"
#include "../../managers/Assets.h"
#include "../../renderer/Renderer.h"
#include "../../input/MouseManager.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static Renderer* renderer;
		static MouseManager* mouse;
};

Button::Button(int c_x, int c_y, std::string title, std::function<void()> press_function, 
			   int font_size, SDL_Colour colour) {
	x = c_x;
	y = c_y;
	src_rect.x = 0; src_rect.y = 0;
	src_rect.w = universe->assets->button_sheet->width; src_rect.h = 64;
	rect.x = x; rect.y = y;
	rect.w = src_rect.w; rect.h = 64;
	text = new Text(c_x, c_y, font_size, colour, title, true, src_rect.w, CENTER);
}

Button::~Button() {
	delete text;
}

void Button::render() {
	src_rect.y = 0;
	if (x > universe->mouse->mouse_pos.x - rect.w && x < universe->mouse->mouse_pos.x) {
		if (y > universe->mouse->mouse_pos.y - rect.h && y < universe->mouse->mouse_pos.y) {
			src_rect.y = src_rect.h;
			if (universe->mouse->mouse_released) {
				if (press_function) { press_function(); }
			}else if (universe->mouse->mouse_down) {
				src_rect.y = src_rect.h * 2;
			}
		}
	}

	universe->renderer->render(universe->assets->button_sheet, &src_rect, &rect);
	text->render();
}

void Button::set_pos(int c_x, int c_y) {
	x = c_x; y = c_y;
	rect.x = x; rect.y = y;
	text->origin_x = x; text->origin_y = y + 16;
	text->update_alignment();
}