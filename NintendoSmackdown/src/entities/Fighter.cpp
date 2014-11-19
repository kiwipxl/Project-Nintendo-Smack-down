#include "Fighter.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"
#include "../managers/Assets.h"
#include "../ui/UIManager.h"
#include "../input/KeyboardManager.h"

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
	fightersheet = universe->assets->fightersheets[0];
	srcrect.x = 0; srcrect.y = 0;

	rect.x = 0; rect.y = 0;
	rect.w = 64; rect.h = 64;
	animator = new Animator(fightersheet.t, &srcrect, 64, 64, 20, true);
	animator->updatetexture(fightersheet.t, 64, 64);

	speedx = 0;
	gravity = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	origin.x = fightersheet.width / 2;
	origin.y = fightersheet.height / 2;
}

void Fighter::update() {
	coords.x = pos.x / 32;
	coords.y = pos.y / 32;
	if (coords.x < 0) { coords.x = 0;
	}else if (coords.x >= universe->map->gridwidth - 1) { coords.x = universe->map->gridwidth - 1; }
	if (coords.y < 0) { coords.y = 0;
	}else if (coords.y >= universe->map->gridheight - 1) { coords.y = universe->map->gridheight - 1; }

	Node* node = universe->map->nodes[(int)coords.x][(int)coords.y];
	if (universe->keyboard->rightkeydown) {
		speedx += movespeed;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
	}else if (universe->keyboard->leftkeydown) {
		speedx -= movespeed;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
	}
	if (speedx > 0 && (node = collideright(coords.x, coords.y)) && node->solid) { speedx = 0; pos.x = ((int)coords.x + .5f) * 32; }
	if (speedx < 0 && (node = collideleft(coords.x, coords.y)) && node->solid) { speedx = 0; pos.x = ((int)coords.x + .5f) * 32; }

	if (speedx >= maxspeed) { speedx = maxspeed;
	}else if (speedx <= -maxspeed) { speedx = -maxspeed; }
	speedx = speedx * friction;
	pos.x += speedx;

	gravity += fallspeed;
	if (gravity > 0 && (node = collidedown(coords.x, coords.y)) && node->solid) {
		gravity = 0;
		pos.y = (int)coords.y * 32;
		if (universe->keyboard->upkeydown) {
			gravity = -jumpheight;
		}
	}
	if (gravity < 0 && (node = collideup(coords.x, coords.y)) && node->solid) {
		gravity = 0;
		pos.y = (int)coords.y * 32;
	}
	if (gravity >= maxfallspeed) { gravity = maxfallspeed; }

	pos.y += gravity;

	rect.x = pos.x; rect.y = pos.y;
	animator->update();

	SDL_RenderCopyEx(universe->winmanager->renderer, fightersheet.t, &srcrect, &rect, 0, &origin, flip);
}

Node* Fighter::collideright(float x, float y) {
	if (x < universe->map->gridwidth - 1 && y < universe->map->gridheight - 1 && universe->map->nodes[x + 1.5f][y + 1]->solid) {
		return universe->map->nodes[x + 1.5f][y + 1];
	}else if (x < universe->map->gridwidth - 1 && y < universe->map->gridheight - 1 && universe->map->nodes[x + 1.5f][y]->solid) {
		return universe->map->nodes[x + 1.5f][y];
	}
	return NULL;
}

Node* Fighter::collideleft(float x, float y) {
	if (y < universe->map->gridheight - 1 && universe->map->nodes[x][y + 1]->solid) {
		return universe->map->nodes[x][y + 1];
	}else if (universe->map->nodes[x][y]->solid) {
		return universe->map->nodes[x][y];
	}
	return NULL;
}

Node* Fighter::collideup(float x, float y) {
	if (y > 0 && x > 0 && x < universe->map->gridwidth - 1 && universe->map->nodes[x + .6f][y - 1]->solid) {
		return universe->map->nodes[x + .6f][y - 1];
	}else if (y > 0 && x > 0 && x < universe->map->gridwidth - 1 && universe->map->nodes[x + 1.4f][y - 1]->solid) {
		return universe->map->nodes[x + 1.4f][y - 1];
	}
	return NULL;
}

Node* Fighter::collidedown(float x, float y) {
	if (x <= universe->map->gridwidth - 1 && y < universe->map->gridheight - 1 && universe->map->nodes[x + 1][y + 2]->solid) {
		return universe->map->nodes[x + 1][y + 2];
	}else if (x <= universe->map->gridwidth - 1 && y < universe->map->gridheight - 1 && universe->map->nodes[x + 1.2f][y + 2]->solid) {
		return universe->map->nodes[x + 1.2f][y + 2];
	}else if (x <= universe->map->gridwidth - 1 && y < universe->map->gridheight - 1 && universe->map->nodes[x + .8f][y + 2]->solid) {
		return universe->map->nodes[x + .8f][y + 2];
	}
	return NULL;
}