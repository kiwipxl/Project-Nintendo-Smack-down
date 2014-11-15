#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "Text.h"

class UIManager : Universal {

	public:
		void initiate();
		void update();
		void render();

		void updatefpstext(int fps);

	private:
		Text* fpstext;
};

#endif