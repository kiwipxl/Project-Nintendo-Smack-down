#include "Movement.h"
#include <iostream>
#include "../../../managers/WindowManager.h"
#include "../../../map/Map.h"
#include "../../../map/Collision.h"
#include "../../../managers/Assets.h"
#include "../Fighter.h"
#include "../../../map/Camera.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Map* map;
		static Assets* assets;
		static Camera* camera;
};

Movement::Movement() {
	//setup the moves from the inputted fither
	moves = CaptainFalcon();

	//setup animation
	animationsheet = muniverse->assets->fightersheets[0];
	srcrect.x = 0; srcrect.y = 0;
	rect.x = 0; rect.y = 0;
	animator = new Animator(animationsheet, &srcrect, 64, 64, 5, true, true);

	//setup initial movement values
	speedx = 0;
	gravity = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;

	doublejump = false;
	lockmoveupdate = false;
	holdingjump = false;
	grabbingedge = false;
	restrictinputx = false;
	restrictinputy = false;
	dashing = false;
	floorcollided = false;
	sliding = false;

	punchtimer = 0;
	punchcycle = moves.IDLE;
	rotation = 0;
	dashcooldowntimer = 0;
	slidingcooldowntimer = 0;

	forcex = 0;

	updatemove(moves.JUMP, 10, false);
}

/**
updates the movement
**/
void Movement::updatemovement() {
	/**
	------------------------------------------------------------------------------------------
											GET COORDS
	------------------------------------------------------------------------------------------
	**/
	rect.w = 64; rect.h = 64;

	//update coords based on position and tile size
	coords.x = (pos.x * muniverse->camera->scale) / muniverse->camera->gridsize;
	coords.y = (pos.y * muniverse->camera->scale) / muniverse->camera->gridsize;
	//make sure the coords don't go out of the grid boundaries
	if (coords.x < 0) { coords.x = 0; }else if (coords.x >= muniverse->map->gridwidth - 1) {
		coords.x = muniverse->map->gridwidth - 1;
	}
	if (coords.y < 0) { coords.y = 0; }else if (coords.y >= muniverse->map->gridheight - 1) {
		pos.y = 0; gravity = 0; coords.y = muniverse->map->gridheight - 1;
	}

	//get the current node based on the coords
	Node* node = muniverse->map->nodes[(int)coords.x][(int)coords.y];

	/**
	------------------------------------------------------------------------------------------
								LEFT/RIGHT MOVEMENT + COLLISION
	------------------------------------------------------------------------------------------
	**/
	//apply movement to speedx if the right key or left key is down
	if (currentmove != moves.CROUCH && !grabbingedge && !restrictinputx) {
		if (rightkeydown) {
			speedx += movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_NONE;
		}else if (leftkeydown) {
			speedx -= movespeed;
			flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
	}

	rightcollided = false;
	leftcollided = false;

	//check for left and right tile collision
	if ((node = Collision::collideright(coords.x, coords.y)) && node->solid) {
		//snap against right solid tile
		if (speedx >= 0) {
			speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
		}
		rightcollided = true;
	}else if ((node = Collision::collideleft(coords.x, coords.y)) && node->solid) {
		//snap against left solid tile
		if (speedx <= 0) {
			speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
		}
		leftcollided = true;
	}

	//limit speedx from going over the max speed
	if (speedx >= maxspeed) { speedx = maxspeed;
	}else if (speedx <= -maxspeed) { speedx = -maxspeed; }
	//apply friction to speedx
	speedx = speedx * friction;

	/**
	------------------------------------------------------------------------------------------
										EDGE GRABBING
	------------------------------------------------------------------------------------------
	**/
	//check to see if you can collide down on the tile for an edge grab as well as a non solid tile below
	if (rightcollided && !grabbingedge && gravity >= 0 &&
		(node = Collision::collidedown(coords.x + 1, coords.y - 1)) && node->solid && node->edgeempty && 
		Collision::collidedown(coords.x, coords.y) == NULL &&
		Collision::collidedown(coords.x + 1, coords.y - 2) == NULL) {
		//snap against the tile in x and y and reset variables
		gravity = 0;
		rotation = 0;
		speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
		pos.y = ((int)coords.y + 1) * 32;
		updatemove(moves.EDGEGRAB, 1, false);
		grabbingedge = true;
		doublejump = false;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
		edgenode = node;
		edgenode->edgeempty = false;
	}else if (leftcollided && !grabbingedge && gravity >= 0 &&
		(node = Collision::collidedown(coords.x - 1, coords.y - 1)) && node->solid && node->edgeempty && 
		Collision::collidedown(coords.x, coords.y) == NULL && 
		Collision::collidedown(coords.x - 1, coords.y - 2) == NULL) {
		//snap against the tile in x and y and reset variables
		gravity = 0;
		rotation = 0;
		speedx = 0; forcex = 0; pos.x = ((int)coords.x + .5f) * 32;
		pos.y = ((int)coords.y + 1) * 32;
		updatemove(moves.EDGEGRAB, 1, false);
		grabbingedge = true;
		doublejump = false;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		edgenode = node;
		edgenode->edgeempty = false;
	}

	if (grabbingedge) {
		updatemove(moves.EDGEGRAB, 1, false);

		//if the up key or down key is pressed while holding onto an edge
		if (!upkeypressed && upkeydown && !restrictinputy) {
			//if the up key is down then apply a small initial jump and let go of the edge
			gravity = -jumpheight / 1.5f;
			upkeypressed = true;
			holdingjump = true;
			updatemove(moves.JUMP, 10, false);
			grabbingedge = false;
			edgenode->edgeempty = true; edgenode = nullptr;
		}else if (downkeydown && !restrictinputy) {
			//if the down key is down then change moves, reset gravity and let go of the edge
			gravity = 0;
			updatemove(moves.JUMP, 10, false);
			grabbingedge = false;
			edgenode->edgeempty = true; edgenode = nullptr;
		}
	}

	/**
	------------------------------------------------------------------------------------------
								GRAVITY + Y COLLIDE + JUMP
	------------------------------------------------------------------------------------------
	**/
	//apply gravity and collide downwards and upwards with solid tiles
	floorcollided = false;
	if (!grabbingedge) {
		gravity += fallspeed;
		if (gravity > 0) {
			//if the gravity is greater than 0, try colliding downwards
			if ((node = Collision::collidedown(coords.x, coords.y)) && node->solid) {
				//snap to bottom tile and reset variables
				rotation = 0;
				gravity = 0;
				pos.y = (int)coords.y * 32;
				doublejump = false;
				floorcollided = true;
				//if not doing other actions, idle if speed is low and start running if the speed is fast
				if (currentmove != moves.JUMP && currentmove != moves.EDGEGRAB) {
					if (currentmove != moves.CROUCH || 
						(currentmove == moves.CROUCH && !downkeydown)) {
						if (speedx >= 1 || speedx <= -1) {
							updatemove(moves.RUN, 15, true);
						}else if (currentmove != moves.LAND) {
							updatemove(moves.IDLE, 5, true);
						}
					}
				}

				//change to idle after the landing animation has finished
				if (animator->paused && currentmove == moves.LAND) { updatemove(moves.IDLE, 5, true); }
				//play the landing animation after jumping or landing
				if (currentmove == moves.JUMP || currentmove == moves.LAND) {
					updatemove(moves.LAND, 10, false);
				}
			}
		}

		//limit gravity to the max fall speed
		if (gravity >= maxfallspeed) { gravity = maxfallspeed; }

		//change the move to jump when walked off solid platform
		if (floorcollided) {
			if (gravity > 0 && (currentmove == moves.IDLE || currentmove == moves.RUN ||
				currentmove == moves.CROUCH || currentmove == moves.DASHATTACK || 
				currentmove == moves.SLIDEATTACK)) {
				updatemove(moves.JUMP, 10, false);
			}
		}

		//if the gravity is less than 0 and colliding up with a solid tile, then snap to the tile
		if (gravity < 0 && (node = Collision::collideup(coords.x, coords.y)) && node->solid) {
			gravity = 0;
			pos.y = ((int)coords.y + 1) * 32;
		}
	}

	/**
	------------------------------------------------------------------------------------------
											JUMPING
	------------------------------------------------------------------------------------------
	**/
	//if the up key is down then apply a small initial jump and change move
	if (floorcollided) {
		if (!upkeypressed && upkeydown && !restrictinputy) {
			gravity = -jumpheight / 8;
			upkeypressed = true;
			holdingjump = true;
			updatemove(moves.JUMP, 10, false);
		}
	}

	//double jumps and hold for higher jumps
	if (upkeydown && !restrictinputy) {
		//if the up key is down after jumping once then apply a double jump
		if (!upkeypressed && !doublejump) {
			gravity = -jumpheight / 8;
			holdingjump = true;
			doublejump = true;
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

	//apply rotation to double jump depending on direction
	if (currentmove == moves.DOUBLEJUMP) {
		if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { rotation += 15; }else { rotation -= 15; }
	}

	/**
	------------------------------------------------------------------------------------------
										PUNCH ATTACK CYCLE
	------------------------------------------------------------------------------------------
	**/
	//if the a key is pressed while idling or running, cycle between punch, kick and rapid punch
	if (currentmove != moves.DASHATTACK && currentmove != moves.CROUCH) {
		if (currentmove == moves.IDLE || (currentmove == moves.RUN && 
			!rightkeydown && !leftkeydown)) {
			if (akeydown) {
				if (!akeypressed) {
					if ((punchcycle == moves.KICK || punchcycle == moves.RAPIDPUNCH) && 
						punchtimer <= PUNCHCYCLETIME) {
						//change move to rapid punch
						updatemove(moves.RAPIDPUNCH, 15, false, true);
						punchcycle = moves.RAPIDPUNCH;
						mparent->dealtdamage = false;
					}else if (punchcycle == moves.PUNCH && punchtimer <= PUNCHCYCLETIME) {
						//change move to kick
						updatemove(moves.KICK, 15, false, true);
						punchcycle = moves.KICK;
						mparent->dealtdamage = false;
					}else {
						//change move to punch
						updatemove(moves.PUNCH, 10, false, true);
						punchcycle = moves.PUNCH;
						mparent->dealtdamage = false;
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

	/**
	------------------------------------------------------------------------------------------
										RUN + DASH ATTACK
	------------------------------------------------------------------------------------------
	**/
	//if the dash attack is not on cooldown then perform a dash attack when the a is pressed
	if (!dashing) { ++dashcooldowntimer; }
	if (currentmove == moves.RUN && dashcooldowntimer >= DASHCOOLDOWN) {
		if (akeydown) {
			if (!akeypressed) {
				//apply force depending on flip direction
				if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { forcex += 10; }else { forcex -= 10; }
				//update movement and restrict movement input
				updatemove(moves.DASHATTACK, 10, false, true);
				restrictinputx = true;
				restrictinputy = true;
				akeypressed = true;
				mparent->dealtdamage = false;
				dashing = true;
				dashcooldowntimer = 0;
			}
		}
	}
	//if dashing and slowed down then end dash and allow movement input
	if (dashing && speedx <= 2 && speedx >= -2 && !lockmoveupdate) {
		restrictinputx = false; restrictinputy = false; dashing = false; animator->paused = false;
		updatemove(moves.IDLE, 5, true);
	}

	/**
	------------------------------------------------------------------------------------------
										CROUCH SLIDE ATTACK
	------------------------------------------------------------------------------------------
	**/
	//if the down key is down then change the move to crouch
	if (floorcollided) {
		if (downkeydown && !downkeypressed) {
			if (!restrictinputy && currentmove != moves.SLIDEATTACK) {
				updatemove(moves.CROUCH, 5, false);
			}
		}
	}

	//if the slide attack is not on cooldown then perform a slide attack when the a is pressed
	if (!sliding) { ++slidingcooldowntimer; }
	if (currentmove == moves.CROUCH && slidingcooldowntimer >= SLIDECOOLDOWN) {
		if (akeydown && downkeydown) {
			if (!akeypressed && !downkeypressed) {
				//apply force depending on flip direction
				if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { forcex += 8; }else { forcex -= 8; }
				//update movement and restrict movement input
				updatemove(moves.SLIDEATTACK, 10, false, true);
				restrictinputx = true;
				restrictinputy = true;
				akeypressed = true;
				downkeypressed = true;
				sliding = true;
				mparent->dealtdamage = false;
				slidingcooldowntimer = 0;
				speedx += forcex;
			}
		}
	}
	//if sliding and slowed down then end slide and allow movement input
	if (sliding && speedx <= 1 && speedx >= -1 && !lockmoveupdate) {
		restrictinputx = false; restrictinputy = false; sliding = false; animator->paused = false;
		updatemove(moves.IDLE, 5, true);
	}

	/**
	------------------------------------------------------------------------------------------
										APPLY VALUES
	------------------------------------------------------------------------------------------
	**/
	//set keyboard keys to false when they aren't being pressed
	if (!akeydown) { akeypressed = false; }
	if (!downkeydown) { downkeypressed = false; }
	if (!upkeydown) { upkeypressed = false; holdingjump = false; }

	//apply force friction to forcex
	forcex = forcex * FORCEFRICTION;

	//apply speedx and gravity to the position
	pos.x += speedx;
	pos.y += gravity;
	//apply forcex to the position
	pos.x += forcex;

	//if the animation is locked and has looped once then unlock it
	if (lockmoveupdate && animator->paused) {
		lockmoveupdate = false;
		if (currentmove == moves.HIT && !floorcollided) { updatemove(moves.JUMP, 10, false); }
	}

	//update the animator
	animator->update();
}

/**
changes the current move to a new move and updates the animation
**/
void Movement::updatemove(int newmove, int fps, bool loop, bool lock) {
	if (currentmove != newmove) {
		if (!lockmoveupdate || lock) {
			currentmove = newmove;
			animationsheet = muniverse->assets->fightersheets[0];
			animator->updatetexture(animationsheet, 64, 64, moves.moveframes[currentmove], 1);
			animator->setfps(fps);
			animator->loop = loop;
			animator->paused = false;
			srcrect.y = currentmove * 64;
			lockmoveupdate = lock;
		}
	}
}

/**
adds force in positive or negative direction depending on flip parameter
**/
void Movement::addflipforce(SDL_RendererFlip newflip, float forcemultiplierx, float forcemultipliery) {
	if (newflip == SDL_RendererFlip::SDL_FLIP_NONE) {
		addforce(forcemultiplierx, forcemultipliery);
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
	}else {
		addforce(-forcemultiplierx, forcemultipliery);
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
	}
}

/**
adds force depending on health
**/
void Movement::addforce(float forcemultiplierx, float forcemultipliery) {
	forcex += ((mparent->health / 100.f) + 1) * forcemultiplierx;
	gravity -= ((mparent->health / 100.f) + 1) * forcemultipliery;
	if (grabbingedge) {
		grabbingedge = false; edgenode->edgeempty = true; edgenode = nullptr; updatemove(moves.JUMP, 10, false);
	}
	updatemove(moves.HIT, 5, false, true);
}