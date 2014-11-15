#include "Item.h"
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

Item::Item(int x, int y) {
	pos.x = x; pos.y = y;
	rect.w = 8; rect.h = 8;
}

void Item::update() {
	rect.x = pos.x; rect.y = pos.y;
}

void Item::render() {
	SDL_RenderCopy(universe->winmanager->renderer, NULL, NULL, &rect);
}