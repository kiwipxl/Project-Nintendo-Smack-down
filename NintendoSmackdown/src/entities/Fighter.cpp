#include "Fighter.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"
#include "../managers/Assets.h"
#include "../ui/UIManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Map* map;
		static Assets* assets;
		static UIManager* uimanager;
};

Fighter::Fighter(int x, int y) {
	pos.x = x; pos.y = y;
	srcrect.x = 0; srcrect.y = 0;
	srcrect.w = 42; srcrect.h = 60;
	rect.x = 0; rect.y = 0;
	rect.w = 42; rect.h = 60;
	animator = new Animator(&srcrect, 8, rect.w, rect.h, rect.w * 4, rect.h * 4, true);
}

void Fighter::update() {
	rect.x = pos.x; rect.y = pos.y;
	animator->update();
}

void Fighter::render() {
	SDL_RenderCopy(universe->winmanager->renderer, universe->assets->captainfalconidle, &srcrect, &rect);
}