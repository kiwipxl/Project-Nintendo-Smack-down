#ifndef MESSAGE_BOX_MANAGER_H
#define MESSAGE_BOX_MANAGER_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "components/Text.h"
#include "components/DropdownBox.h"
#include "components/Button.h"
#include "components/MessageBox.h"

class MessageBoxManager : Universal {

	public:
		void create(MessageBox* c_message_box);
		void update();
		void remove();

		void resize_update(int w = 0, int h = 0);

		void remove_message_box();

	private:
		MessageBox* message_box = NULL;
};

#endif