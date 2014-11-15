#include "Bullet.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"
#include "../managers/Assets.h"
#include "../ui/UIManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Assets* assets;
};

Bullet::Bullet(int x, int y, float rotation) {
	pos.x = x; pos.y = y;
	rect.w = 8; rect.h = 8;
	speedx = 5 * cos(rotation);
	speedy = 5 * -sin(rotation);
	removed = false;
	removetimer = 0;
}

void Bullet::update() {
	if (removed) { return; }
	pos.x += speedx;
	pos.y += speedy;
	rect.x = pos.x; rect.y = pos.y;

	++removetimer;
	if (removetimer >= 100) {
		removed = true;
	}
}

void Bullet::render() {
	SDL_RenderCopy(universe->winmanager->renderer, universe->assets->bullet, NULL, &rect);
}