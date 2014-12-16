#ifndef MESSAGE_BOX_MANAGER_H
#define MESSAGE_BOX_MANAGER_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"
#include "components/Button.h"
#include "components/MessageBox.h"

enum DialogType {
	OK,
	CANCEL_OK, 
	NO_YES, 
};

class MessageBoxManager : Universal {

	public:
		void show(MessageBox* c_message_box, DialogType type);
		void update();
		void hide();

		void resize_update(int w = 0, int h = 0);

		void change_press_function(int button_index, std::function<void()> press_function);
		void add_custom_button(Button* button);

	private:
		MessageBox* message_box = NULL;

		void remove_message_box();
};

#endif