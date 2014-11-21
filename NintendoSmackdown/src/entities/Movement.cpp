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
	//setup the moves from the inputted fither
	moves = CaptainFalcon();

	//setup animation
	animationsheet = universe->assets->fightersheets[0];
	srcrect.x = 0; srcrect.y = 0;
	rect.x = 0; rect.y = 0;
	rect.w = 64; rect.h = 64;
	animator = new Animator(animationsheet, &srcrect, 64, 64, 5, true, true);

	//setup initial movement values
	speedx = 0;
	gravity = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;
	origin.x = 32;
	origin.y = 32;

	upkeypressed = false;
	doubleupkeypressed = false;
	lockmoveupdate = false;
	holdingjump = false;
	grabbingedge = false;
	restrictinputx = false;
	restrictinputy = false;
	akeypressed = false;
	dashing = false;

	punchtimer = 0;
	punchcycle = moves.IDLE;
	rotation = 0;
	dashcooldowntimer = 0;

	forcex = 0;
	forcey = 0;

	updatemove(moves.JUMP, 10, false);
}

/**
updates the movement
**/
void Movement::updatemovement() {
	//update coords based on position and tile size
	coords.x = pos.x / 32;
	coords.y = pos.y / 32;
	//make sure the coords don't go out of the grid boundaries
	if (coords.x < 0) { coords.x = 0; }else if (coords.x >= universe->map->gridwidth - 1) {
		coords.x = universe->map->gridwidth - 1;
	}
	if (coords.y < 0) { coords.y = 0; }else if (coords.y >= universe->map->gridheight - 1) {
		pos.y = 0; gravity = 0; coords.y = universe->map->gridheight - 1;
	}

	//get the current node based on the coords
	Node* node = universe->map->nodes[(int)coords.x][(int)coords.y];

	//apply movement to speedx if the right key or left key is down
	if (currentmove != moves.CROUCH && !grabbingedge && !restrictinputx) {
		if (universe->keyboard->rightkeydown) {
			speedx += movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}else if (universe->keyboard->leftkeydown) {
			speedx -= movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
	}

	//check for left and right tile collision
	if ((node = Collision::collideright(coords.x, coords.y)) && node->solid) {
		//snap against right solid tile
		if (speedx >= 0) { speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32; }
		//check to see if you can collide down on the tile for an edge grab as well as a non solid tile below
		if (!grabbingedge && gravity >= 0 && 
			(node = Collision::collidedown(coords.x + 1, coords.y - 1)) && node->solid && 
			Collision::collidedown(coords.x, coords.y) == NULL && 
			Collision::collidedown(coords.x + 1, coords.y - 2) == NULL) {
			//snap against the tile in x and y and reset variables
			gravity = 0;
			rotation = 0;
			speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
			pos.y = ((int)coords.y + 1) * 32;
			updatemove(moves.EDGEGRAB, 2, true);
			grabbingedge = true;
			doubleupkeypressed = false;
			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}
	}else if ((node = Collision::collideleft(coords.x, coords.y)) && node->solid) {
		//snap against left solid tile
		if (speedx <= 0) { speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32; }
		//check to see if you can collide down on the tile for an edge grab as well as a non solid tile below
		if (!grabbingedge && gravity >= 0 && 
			(node = Collision::collidedown(coords.x - 1, coords.y - 1)) && node->solid && 
			Collision::collidedown(coords.x, coords.y) == NULL && 
			Collision::collidedown(coords.x - 1, coords.y - 2) == NULL) {
			//snap against the tile in x and y and reset variables
			gravity = 0;
			rotation = 0;
			speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
			pos.y = ((int)coords.y + 1) * 32;
			updatemove(moves.EDGEGRAB, 2, true);
			grabbingedge = true;
			doubleupkeypressed = false;
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
	}

	//limit speedx from going over the max speed
	if (speedx >= maxspeed) { speedx = maxspeed;
	}else if (speedx <= -maxspeed) { speedx = -maxspeed; }
	//apply friction to speedx
	speedx = speedx * friction;

	//change the move to jump when walked off solid platform
	if (gravity > 0 && (currentmove == moves.IDLE || currentmove == moves.RUN || 
		currentmove == moves.CROUCH || currentmove == moves.DASHATTACK)) {
		updatemove(moves.JUMP, 10, false);
	}

	//apply rotation to double jump depending on direction
	if (currentmove == moves.DOUBLEJUMP) {
		if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { rotation += 15; }else { rotation -= 15; }
	}

	//apply gravity and collide downwards and upwards with solid tiles
	if (!grabbingedge) {
		gravity += fallspeed;
		if (gravity > 0) {
			//if the gravity is greater than 0, try colliding downwards
			if ((node = Collision::collidedown(coords.x, coords.y)) && node->solid) {
				//snap to bottom tile and reset variables
				rotation = 0;
				gravity = 0;
				pos.y = (int)coords.y * 32;
				doubleupkeypressed = false;

				//if not doing other actions, idle if speed is low and start running if the speed is fast
				if (currentmove != moves.JUMP && currentmove != moves.JUMP && currentmove != moves.EDGEGRAB) {
					if (speedx >= 1 || speedx <= -1) {
						updatemove(moves.RUN, 15, true);
					}else if (currentmove != moves.LAND) {
						updatemove(moves.IDLE, 5, true);
					}
				}

				//change to idle after the landing animation has finished
				if (animator->paused && currentmove == moves.LAND) { updatemove(moves.IDLE, 5, true); }
				//play the landing animation after jumping or landing
				if (currentmove == moves.JUMP || currentmove == moves.LAND) {
					updatemove(moves.LAND, 10, false);
				}

				//if the up key is down then apply a small initial jump and change move
				if (!upkeypressed && universe->keyboard->upkeydown && !restrictinputy) {
					gravity = -jumpheight / 8;
					upkeypressed = true;
					holdingjump = true;
					updatemove(moves.JUMP, 10, false);
				}else if (universe->keyboard->downkeydown && !restrictinputy) {
					//if the down key is down then change the move to crouch
					updatemove(moves.CROUCH, 5, false);
				}
			}
		}
		//double jumps and hold for higher jumps
		if (universe->keyboard->upkeydown && !restrictinputy) {
			//if the up key is down after jumping once then apply a double jump
			if (!upkeypressed && !doubleupkeypressed) {
				gravity = -jumpheight / 8;
				holdingjump = true;
				doubleupkeypressed = true;
				upkeypressed = true;
				updatemove(moves.DOUBLEJUMP, 15, false);
			}
			//makes jump longer as long as up key is down or until the jump height limit is reached
			if (holdingjump) {
				gravity -= fallspeed * 4;
				if (gravity <= -jumpheight) {
					holdingjump = false;
				}
			}
		}

		//if the gravity is less than 0 and colliding up with a solid tile, then snap to the tile
		if (gravity < 0 && (node = Collision::collideup(coords.x, coords.y)) && node->solid) {
			gravity = 0;
			pos.y = ((int)coords.y + 1) * 32;
		}

		//limit gravity to the max fall speed
		if (gravity >= maxfallspeed) { gravity = maxfallspeed; }
	}else {
		//if the up key or down key is pressed while holding onto an edge
		if (!upkeypressed && universe->keyboard->upkeydown && !restrictinputy) {
			//if the up key is down then apply a small initial jump and let go of the edge
			gravity = -jumpheight / 1.5f;
			upkeypressed = true;
			holdingjump = true;
			updatemove(moves.JUMP, 10, false);
			grabbingedge = false;
		}else if (universe->keyboard->downkeydown && !restrictinputy) {
			//if the down key is down then change moves, reset gravity and let go of the edge
			gravity = 0;
			updatemove(moves.JUMP, 10, false);
			grabbingedge = false;
		}
	}

	//if the a key is pressed while idling or running, cycle between punch, kick and rapid punch
	if (currentmove != moves.DASHATTACK) {
		if (currentmove == moves.IDLE || (currentmove == moves.RUN && 
			!universe->keyboard->rightkeydown && !universe->keyboard->leftkeydown)) {
			if (universe->keyboard->akeydown) {
				if (!akeypressed) {
					if ((punchcycle == moves.KICK || punchcycle == moves.RAPIDPUNCH) && 
						punchtimer <= PUNCHCYCLETIME) {
						//change move to rapid punch
						updatemove(moves.RAPIDPUNCH, 15, false, true);
						punchcycle = moves.RAPIDPUNCH;
					}else if (punchcycle == moves.PUNCH && punchtimer <= PUNCHCYCLETIME) {
						//change move to kick
						updatemove(moves.KICK, 15, false, true);
						punchcycle = moves.KICK;
					}else {
						//change move to punch
						updatemove(moves.PUNCH, 10, false, true);
						punchcycle = moves.PUNCH;
					}
					//restrict movement input and reset punch timer
					punchtimer = 0;
					restrictinputx = true;
					restrictinputy = true;
					akeypressed = true;
				}
			}
		}
	}

	//increment punchtimer and allow movement input after a move in the punch cycle has been performed
	if (currentmove != moves.PUNCH && currentmove != moves.KICK && currentmove != moves.RAPIDPUNCH) {
		if (punchcycle != moves.IDLE) {
			restrictinputx = false; restrictinputy = false;
			++punchtimer;
			if (punchtimer >= PUNCHCYCLETIME) { punchtimer = 0; punchcycle = moves.IDLE; }
		}
	}else {
		//if a punch, kick or rapid punch is being performed then apply friction to speedx
		speedx = speedx * .8f;
	}

	//if the dash attack is not on cooldown then perform a dash attack when the a is pressed
	if (!dashing) { ++dashcooldowntimer; }
	if (currentmove == moves.RUN && dashcooldowntimer >= DASHCOOLDOWN) {
		if (universe->keyboard->akeydown) {
			if (!akeypressed) {
				//apply force depending on flip direction
				if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { forcex += 15; }else { forcex -= 15; }
				//update movement and restrict movement input
				updatemove(moves.DASHATTACK, 8, false, true);
				restrictinputx = true;
				restrictinputy = true;
				akeypressed = true;
				dashing = true;
				dashcooldowntimer = 0;
			}
		}
	}
	//if dashing and slowed down then end dash and allow movement input
	if (dashing && speedx <= 2 && speedx >= -2) {
		restrictinputx = false; restrictinputy = false; dashing = false; animator->paused = true;
	}

	//set keyboard keys to false when they aren't being pressed
	if (!universe->keyboard->akeydown) { akeypressed = false; }
	if (!universe->keyboard->upkeydown) { upkeypressed = false; holdingjump = false; }

	//apply force friction to forcex and forcey
	forcex = forcex * FORCEFRICTION;
	forcey = forcey * FORCEFRICTION;

	//apply speedx and gravity to the position
	pos.x += speedx;
	pos.y += gravity;
	//apply forcex and forcey to the position
	pos.x += forcex;
	pos.y += forcey;

	//if the animation is locked and has looped once then unlock it
	if (lockmoveupdate && animator->paused) {
		lockmoveupdate = false;
	}

	//update the rect and animator
	rect.x = pos.x; rect.y = pos.y;
	animator->update();
}

/**
changes the current move to a new move and updates the animation
**/
void Movement::updatemove(int newmove, int fps, bool loop, bool lock) {
	if (currentmove != newmove) {
		if (!lockmoveupdate || lock) {
			currentmove = newmove;
			animationsheet = universe->assets->fightersheets[0];
			animator->updatetexture(animationsheet, 64, 64, moves.moveframes[currentmove], 1);
			animator->setfps(fps);
			animator->loop = loop;
			animator->paused = false;
			srcrect.y = currentmove * rect.h;
			lockmoveupdate = lock;
		}
	}
}