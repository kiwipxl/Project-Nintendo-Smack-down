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
	fightersheet = universe->assets->fightersheets[0];
	srcrect.x = 0; srcrect.y = 0;

	rect.x = 0; rect.y = 0;
	rect.w = 64; rect.h = 64;
	animator = new Animator(fightersheet, &srcrect, 64, 64, 20, true);
	animator->updatetexture(fightersheet, 64, 64);
}

void Fighter::update() {
	rect.x = pos.x; rect.y = pos.y;
	animator->update();

	SDL_RenderCopy(universe->winmanager->renderer, fightersheet, &srcrect, &rect);
}