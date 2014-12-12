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

Button::Button(int c_x, int c_y, std::string title, std::function<void()> press, 
			   int width, int height, int font_size, SDL_Colour colour) {
	x = c_x;
	y = c_y;
	origin_x = x;
	origin_y = y;
	src_rect.x = 0; src_rect.y = 0;
	src_rect.w = width; src_rect.h = 64;
	rect.x = x; rect.y = y;
	rect.w = width; rect.h = height;
	press_function = press;
	removed = false;
	text = new Text(c_x, c_y, font_size, colour, title, true, src_rect.w, CENTER);
}

Button::~Button() {
	delete text;
	removed = true;
}

void Button::render() {
	if (removed) { return; }

	src_rect.y = 0;
	if (x > universe->mouse->mouse_pos.x - rect.w && x < universe->mouse->mouse_pos.x) {
		if (y > universe->mouse->mouse_pos.y - rect.h && y < universe->mouse->mouse_pos.y) {
			src_rect.y = src_rect.h;
			if (universe->mouse->mouse_released) {
				if (press_function) { press_function(); return; }
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
	text->origin_x = x; text->origin_y = y + ((rect.h / 2) - (text->rect.h / 2));
	text->update_alignment();
}