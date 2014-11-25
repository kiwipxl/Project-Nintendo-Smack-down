#include "Fighter.h"
#include <iostream>
#include "../../managers/WindowManager.h"
#include "../../map/Map.h"
#include "../../managers/Assets.h"
#include "../../ui/UIManager.h"
#include "../../input/KeyboardManager.h"
#include "../../map/Collision.h"
#include "../../map/Camera.h"
#include "../../map/Tiles.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Map* map;
		static Assets* assets;
		static UIManager* uimanager;
		static KeyboardManager* keyboard;
		static Camera* camera;
};

Fighter::Fighter(int x, int y, FighterName fname, FighterType ftype) {
	pos.x = x; pos.y = y;
	name = fname; type = ftype;
	mparent = this;
}

void Fighter::update() {
	if (type == PLAYER) {
		leftkeydown = universe->keyboard->leftkeydown;
		rightkeydown = universe->keyboard->rightkeydown;
		upkeydown = universe->keyboard->upkeydown;
		downkeydown = universe->keyboard->downkeydown;
		akeydown = universe->keyboard->akeydown;
		bkeydown = universe->keyboard->bkeydown;
	}else {

	}
	updatemovement();
	updatedamage();
	rect.x = pos.x + universe->camera->x + universe->camera->getoffsetx(pos.x);
	rect.y = pos.y + universe->camera->y + universe->camera->getoffsety(pos.y);
	rect.w = 64 * universe->camera->scale; rect.h = 64 * universe->camera->scale;
	origin.x = rect.w / 2; origin.y = rect.h / 2;
	SDL_RenderCopyEx(universe->winmanager->renderer, animationsheet->t, &srcrect, &rect, rotation, &origin, flip);
}