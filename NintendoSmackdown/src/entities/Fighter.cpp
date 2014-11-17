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
	rect.x = 0; rect.y = 0;
	rect.w = 42; rect.h = 60;
	fightersheet = universe->assets->captainfalconidle;
	animator = new Animator(fightersheet, &srcrect, rect.w, rect.h, 8, true);
	animator->updatetexture(fightersheet, rect.w, rect.h);
}

void Fighter::update() {
	rect.x = pos.x; rect.y = pos.y;
	animator->update();

	SDL_RenderCopy(universe->winmanager->renderer, fightersheet, &srcrect, &rect);
}