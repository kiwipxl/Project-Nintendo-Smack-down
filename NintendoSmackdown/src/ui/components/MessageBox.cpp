#include "MessageBox.h"
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

MessageBox::MessageBox(int c_x, int c_y, std::string title, std::string message, int message_font_size) {
	x = c_x;
	y = c_y;

	src_rect.x = 0; src_rect.y = 0;
	src_rect.w = universe->assets->messagebox_sheet->width; src_rect.h = universe->assets->messagebox_sheet->height;

	rect.x = x; rect.y = y;
	rect.w = src_rect.w; rect.h = src_rect.h;

	bg_src_rect.x = 1; bg_src_rect.y = 0; bg_src_rect.w = 1; bg_src_rect.h = 1;
	bg_rect.x = 0; bg_rect.y = 0; bg_rect.w = 0; bg_rect.h = 0;

	title_text = new Text(0, 0, 20, { 0, 0, 0 }, title, true, src_rect.w, LEFT);
	message_text = new Text(0, 0, message_font_size, { 0, 0, 0 }, message, true, src_rect.w, CENTER);

	removed = false;

	set_pos(x, y);
	resize_update();
}

MessageBox::~MessageBox() {
	delete title_text;
	delete message_text;
	for (Button* &button : buttons) {
		delete button;
	}
	buttons.clear();
	removed = true;
}

void MessageBox::render() {
	if (removed) { return; }

	universe->assets->plain_colours->set_colour(1, 1, 1, .75f);
	universe->renderer->render(universe->assets->plain_colours, &bg_src_rect, &bg_rect);

	universe->renderer->render(universe->assets->messagebox_sheet, &src_rect, &rect);

	title_text->render();
	message_text->render();

	for (int n = 0; n < buttons.size(); ++n) {
		if (n < buttons.size()) {
			buttons[n]->render();
			if (removed) { return; }
		}
	}
}

void MessageBox::set_pos(int c_x, int c_y) {
	x = c_x; y = c_y;
	rect.x = x; rect.y = y;

	title_text->origin_x = x + 16; title_text->origin_y = y + 4;
	title_text->update_alignment();
	
	message_text->origin_x = x; message_text->origin_y = y + 64;
	message_text->update_alignment();

	for (Button* button : buttons) {
		button->set_pos(button->origin_x + x, button->origin_y + y);
	}
}

void MessageBox::resize_update(int w, int h) {
	if (w == 0 && h == 0) {
		w = universe->win_manager->screen_width;
		h = universe->win_manager->screen_height;
	}

	bg_rect.w = w; bg_rect.h = h;
}

void MessageBox::add_button(Button* button) {
	buttons.push_back(button);
}