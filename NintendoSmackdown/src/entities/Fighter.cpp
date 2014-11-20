#include "Fighter.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"
#include "../managers/Assets.h"
#include "../ui/UIManager.h"
#include "../input/KeyboardManager.h"
#include "../map/Collision.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Map* map;
		static Assets* assets;
		static UIManager* uimanager;
		static KeyboardManager* keyboard;
};

Fighter::Fighter(int x, int y) {
	pos.x = x; pos.y = y;
}

void Fighter::update() {
	updatemovement();
	SDL_RenderCopyEx(universe->winmanager->renderer, animationsheet->t, &srcrect, &rect, rotation, &origin, flip);
}