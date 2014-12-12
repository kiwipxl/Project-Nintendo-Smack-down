#include "DropdownBox.h"
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

DropdownBox::DropdownBox(int c_x, int c_y) {
	x = c_x;
	y = c_y;
	src_rect.x = 0; src_rect.y = 0;
	src_rect.w = 160; src_rect.h = 28;
	rect.x = x; rect.y = y;
	rect.w = 160; rect.h = 28;
	selected_box = add_box("", nullptr, { 200, 100, 0 });
}

DropdownBox::~DropdownBox() {
	for (DropBox* &box : boxes) {
		box->remove();
		delete box;
	}
	boxes.clear();
}

DropBox* DropdownBox::add_box(std::string title, std::function<void()> press_function, SDL_Colour colour) {
	DropBox* box = new DropBox(boxes.size(), x, y, title, colour);
	box->press_function = press_function;
	boxes.push_back(box);
	opened = false;
	return box;
}

void DropdownBox::open() {
	int dest_y = y;
	for (DropBox* box : boxes) {
		box->dest_y = dest_y;
		dest_y += rect.h;
	}
	opened = true;
}

void DropdownBox::close() {
	for (DropBox* box : boxes) {
		box->dest_y = y;
	}
	opened = false;
}

void DropdownBox::select(int index, bool call_press) {
	selected_box->text->render_text(boxes[index]->text->get_text(), true);
	selected_box->id = index;

	if (call_press && boxes[index]->press_function) {
		boxes[index]->press_function();
	}
}

void DropdownBox::render() {
	bool selected = false;
	hover_box = nullptr;
	if (x > universe->mouse->mouse_pos.x - rect.w && x < universe->mouse->mouse_pos.x) {
		for (DropBox* box : boxes) {
			if (box->y > universe->mouse->mouse_pos.y - rect.h && box->y < universe->mouse->mouse_pos.y) {
				if (universe->mouse->mouse_released) {
					selected = true;
					if (opened) {
						select(box->id, true);
						close();
					}else {
						open();
					}
				}else {
					hover_box = box;
				}
				break;
			}
		}
	}

	if (universe->mouse->mouse_released && !selected) {
		close();
	}

	for (DropBox* box : boxes) {
		src_rect.y = 0;
		box->y -= (box->y - box->dest_y) / 2.5f;
		rect.y = box->y;

		if (box == hover_box) { src_rect.y = src_rect.h; }
		if (selected_box->id == box->id) { src_rect.y = src_rect.h * 2; }
		if (selected_box->id == box->id && box == hover_box) { src_rect.y = src_rect.h * 3; }

		if (box != selected_box) {
			universe->renderer->render(universe->assets->dropdown_box_sheet, &src_rect, &rect);
			box->text->rect.y = rect.y + 2;
			box->text->render();
		}
	}

	src_rect.y = src_rect.h * 2;
	if (selected_box == hover_box) { src_rect.y = src_rect.h * 3; }
	rect.y = y;
	universe->renderer->render(universe->assets->dropdown_box_sheet, &src_rect, &rect);
	selected_box->text->rect.y = rect.y + 2;
	selected_box->text->render();
}