#include "Movement.h"
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

Movement::Movement() {
	move = IDLE;
	animationsheet = universe->assets->fightersheets[move];
	srcrect.x = 0; srcrect.y = 0;

	rect.x = 0; rect.y = 0;
	rect.w = 64; rect.h = 64;
	animator = new Animator(animationsheet, &srcrect, 64, 64, 5, true);

	speedx = 0;
	gravity = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	origin.x = 32;
	origin.y = 32;

	jumped = false;
	doublejumped = false;
	lockmoveupdate = false;
	holdingjump = false;
	rotation = 0;
	grabbingedge = false;
}

void Movement::updatemovement() {
	coords.x = pos.x / 32;
	coords.y = pos.y / 32;
	if (coords.x < 0) { coords.x = 0; }else if (coords.x >= universe->map->gridwidth - 1) {
		coords.x = universe->map->gridwidth - 1;
	}
	if (coords.y < 0) { coords.y = 0; }else if (coords.y >= universe->map->gridheight - 1) {
		pos.y = 0; gravity = 0; coords.y = universe->map->gridheight - 1;
	}

	Node* node = universe->map->nodes[(int)coords.x][(int)coords.y];
	if (move != CROUCH && !grabbingedge) {
		if (universe->keyboard->rightkeydown) {
			speedx += movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}else if (universe->keyboard->leftkeydown) {
			speedx -= movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
	}

	if (speedx >= 0 && (node = Collision::collideright(coords.x, coords.y)) && node->solid) {
		speedx = 0; pos.x = ((int)coords.x + .5f) * 32;
		if (gravity >= 0 && (node = Collision::collidedown(coords.x + 1, coords.y - 1)) && node->solid) {
			gravity = 0;
			rotation = 0;
			pos.y = ((int)coords.y + 1) * 32;
			updatemove(EDGEGRAB, 2, true);
			grabbingedge = true;
			doublejumped = false;
		}
	}else if (speedx <= 0 && (node = Collision::collideleft(coords.x, coords.y)) && node->solid) {
		speedx = 0; pos.x = ((int)coords.x + .5f) * 32;
		if (gravity >= 0 && (node = Collision::collidedown(coords.x - 1, coords.y - 1)) && node->solid) {
			gravity = 0;
			rotation = 0;
			pos.y = ((int)coords.y + 1) * 32;
			updatemove(EDGEGRAB, 2, true);
			grabbingedge = true;
			doublejumped = false;
		}
	}

	if (speedx >= maxspeed) { speedx = maxspeed;
	}else if (speedx <= -maxspeed) { speedx = -maxspeed; }
	speedx = speedx * friction;

	if (gravity > 0 && (move == IDLE || move == RUNNING)) { updatemove(JUMP, 10, false); }

	if (move == ROLL) {
		if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { rotation += 15;
		}else { rotation -= 15; }
	}

	if (!grabbingedge) {
		gravity += fallspeed;
		if (gravity > 0) {
			if ((node = Collision::collidedown(coords.x, coords.y)) && node->solid) {
				rotation = 0;
				gravity = 0;
				pos.y = (int)coords.y * 32;
				doublejumped = false;

				if (move != JUMP && move != ROLL && move != EDGEGRAB) {
					if (speedx >= 1 || speedx <= -1) {
						updatemove(RUNNING, 15, true);
					}else if (move != LAND) {
						updatemove(IDLE, 5, true);
					}
				}

				if (animator->paused && move == LAND) { updatemove(IDLE, 5, true); }
				if (move == JUMP || move == LAND || move == ROLL) { updatemove(LAND, 10, false); }

				if (!jumped && universe->keyboard->upkeydown) {
					gravity = -jumpheight / 8;
					jumped = true;
					holdingjump = true;
					updatemove(JUMP, 10, false);
				}else if (universe->keyboard->downkeydown) {
					updatemove(CROUCH, 5, false);
				}
			}
		}
		if (universe->keyboard->upkeydown) {
			if (!jumped && !doublejumped) {
				gravity = -jumpheight / 8;
				holdingjump = true;
				doublejumped = true;
				jumped = true;
				updatemove(ROLL, 15, false);
			}
			if (holdingjump) {
				gravity -= fallspeed * 4;
				if (gravity <= -jumpheight) {
					holdingjump = false;
				}
			}
		}else {
			jumped = false;
			holdingjump = false;
		}

		if (gravity < 0 && (node = Collision::collideup(coords.x, coords.y)) && node->solid) {
			gravity = 0;
			pos.y = ((int)coords.y + 1) * 32;
		}
		if (gravity >= maxfallspeed) { gravity = maxfallspeed; }
	}else {
		if (!jumped && universe->keyboard->upkeydown) {
			gravity = -jumpheight / 1.5f;
			jumped = true;
			holdingjump = true;
			updatemove(JUMP, 10, false);
			grabbingedge = false;
		}else if (universe->keyboard->downkeydown) {
			gravity = 0;
			updatemove(JUMP, 10, false);
			grabbingedge = false;
		}
	}

	pos.x += speedx;
	pos.y += gravity;

	if (lockmoveupdate && animator->paused) {
		lockmoveupdate = false;
	}

	rect.x = pos.x; rect.y = pos.y;
	animator->update();
}

void Movement::updatemove(Move newmove, int fps, bool loop, bool lock) {
	if (!lockmoveupdate || lock) {
		move = newmove;
		animationsheet = universe->assets->fightersheets[move];
		animator->updatetexture(animationsheet, 64, 64);
		animator->setfps(fps);
		animator->loop = loop;
		animator->paused = false;
		lockmoveupdate = lock;
	}
}