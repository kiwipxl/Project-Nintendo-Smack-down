#include "MessageBoxManager.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../managers/Assets.h"
#include "../input/InputManager.h"
#include "../managers/StateManager.h"
#include "../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static InputManager* input;
		static StateManager* state;
		static Renderer* renderer;
};

void MessageBoxManager::create(MessageBox* c_message_box) {
	message_box = c_message_box;
	message_box->add_button(new Button(message_box->rect.w - 140, message_box->rect.h - 55, "OK",
		[this](void) { remove_message_box(); }, 110, 40));

	resize_update();
}

void MessageBoxManager::update() {
	if (message_box != NULL) { message_box->render(); }
}

void MessageBoxManager::remove() {
	remove_message_box();
}

void MessageBoxManager::remove_message_box() {
	delete message_box;
	message_box = NULL;
}

void MessageBoxManager::resize_update(int w, int h) {
	if (w == 0 && h == 0) {
		w = universe->win_manager->screen_width;
		h = universe->win_manager->screen_height;
	}

	if (message_box != NULL) {
		message_box->set_pos((w / 2) - (message_box->get_width() / 2), (h / 2) - (message_box->get_height() / 2));
	}
}