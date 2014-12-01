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
		static WindowManager* win_manager;
		static Map* map;
		static Assets* assets;
		static Camera* camera;
};

Movement::Movement(Fighter* parent) {
	base_parent = parent;

	//setup animation
	animation_sheet = base_universe->assets->fighter_sheets[0];
	src_rect.x = 0; src_rect.y = 0;
	rect.x = 0; rect.y = 0;
	animator = new Animator(animation_sheet, &src_rect, 64, 64, 5, true, true);

	//setup initial movement values
	speed_x = 0;
	gravity = 0;
	flip = SDL_RendererFlip::SDL_FLIP_NONE;

	double_jump = false;
	lock_move_update = false;
	holding_jump = false;
	grabbing_edge = false;
	restrict_input_x = false;
	restrict_input_y = false;
	dashing = false;
	floor_collided = false;
	sliding = false;
	down_air_kick = false;
	right_air_knee = false;
	punching = false;
	air_somersault = false;

	punch_timer = 0;
	punch_cycle = moves.IDLE;
	rotation = 0;
	dash_cooldown_timer = 0;
	sliding_cooldown_timer = 0;

	force_x = 0;

	update_move(moves.JUMP, 10, false);
}

/**
updates the movement
**/
void Movement::update_movement() {
	/**
	------------------------------------------------------------------------------------------
											GET COORDS
	------------------------------------------------------------------------------------------
	**/
	rect.w = 64; rect.h = 64;

	//update coords based on position and tile size
	coords.x = (pos.x * base_universe->camera->scale) / base_universe->camera->grid_size;
	coords.y = (pos.y * base_universe->camera->scale) / base_universe->camera->grid_size;
	//make sure the coords don't go out of the grid boundaries
	if (coords.x < 0) { coords.x = 0; }else if (coords.x >= base_universe->map->grid_width - 1) {
		coords.x = base_universe->map->grid_width - 1;
	}
	if (coords.y < 0) { coords.y = 0; }else if (coords.y >= base_universe->map->grid_height - 1) {
		pos.y = 0; gravity = 0; coords.y = base_universe->map->grid_height - 1;
	}

	//get the current node based on the coords
	Node* node = base_universe->map->nodes[(int)coords.x][(int)coords.y];

	/**
	------------------------------------------------------------------------------------------
								LEFT/RIGHT MOVEMENT + COLLISION
	------------------------------------------------------------------------------------------
	**/
	//apply movement to speedx if the right key or left key is down
	if (current_move != moves.CROUCH && !grabbing_edge && !restrict_input_x) {
		if (right_key_down) {
			speed_x += move_speed;
			if (floor_collided) { flip = SDL_RendererFlip::SDL_FLIP_NONE; }
		}else if (left_key_down) {
			speed_x -= move_speed;
			if (floor_collided) { flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; }
		}
	}

	right_collided = false;
	left_collided = false;

	//check for left and right tile collision
	if ((node = Collision::collide_right(coords.x, coords.y)) && node->solid) {
		//snap against right solid tile
		if (speed_x >= 0) {
			speed_x = 0; force_x = 0; pos.x = ((int)coords.x + .5f) * 32;
		}
		right_collided = true;
	}else if ((node = Collision::collide_left(coords.x, coords.y)) && node->solid) {
		//snap against left solid tile
		if (speed_x <= 0) {
			speed_x = 0; force_x = 0; pos.x = ((int)coords.x + .5f) * 32;
		}
		left_collided = true;
	}

	//limit speedx from going over the max speed
	if (speed_x >= max_speed) { speed_x = max_speed;
	}else if (speed_x <= -max_speed) { speed_x = -max_speed; }
	//apply friction to speedx
	speed_x = speed_x * friction;

	/**
	------------------------------------------------------------------------------------------
										EDGE GRABBING
	------------------------------------------------------------------------------------------
	**/
	//check to see if you can collide_ down on the tile for an edge grab as well as a non solid tile below
	if (right_collided && !grabbing_edge && gravity >= 0 &&
		(node = Collision::collide_down(coords.x + 1, coords.y - 1)) && node->solid && node->edgeempty && 
		Collision::collide_down(coords.x, coords.y) == NULL &&
		Collision::collide_down(coords.x + 1, coords.y - 2) == NULL && 
		Collision::collide_down(coords.x, coords.y - 1) == NULL) {
		//snap against the tile in x and y and reset variables
		gravity = 0;
		rotation = 0;
		speed_x = 0; force_x = 0; pos.x = ((int)coords.x + .5f) * 32;
		pos.y = ((int)coords.y + 1) * 32;
		update_move(moves.EDGE_GRAB, 1, false);
		grabbing_edge = true;
		double_jump = false;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
		edge_node = node;
		edge_node->edgeempty = false;
	}else if (left_collided && !grabbing_edge && gravity >= 0 &&
		(node = Collision::collide_down(coords.x - 1, coords.y - 1)) && node->solid && node->edgeempty && 
		Collision::collide_down(coords.x, coords.y) == NULL && 
		Collision::collide_down(coords.x - 1, coords.y - 2) == NULL && 
		Collision::collide_down(coords.x, coords.y - 1) == NULL) {
		//snap against the tile in x and y and reset variables
		gravity = 0;
		rotation = 0;
		speed_x = 0; force_x = 0; pos.x = ((int)coords.x + .5f) * 32;
		pos.y = ((int)coords.y + 1) * 32;
		update_move(moves.EDGE_GRAB, 1, false);
		grabbing_edge = true;
		double_jump = false;
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		edge_node = node;
		edge_node->edgeempty = false;
	}

	if (grabbing_edge) {
		update_move(moves.EDGE_GRAB, 1, false);

		//if the up key or down key is pressed while holding onto an edge
		if (!up_key_pressed && up_key_down && !restrict_input_y) {
			//if the up key is down then apply a small initial jump and let go of the edge
			gravity = -jump_height / 1.5f;
			up_key_pressed = true;
			holding_jump = true;
			update_move(moves.JUMP, 10, false);
			grabbing_edge = false;
			edge_node->edgeempty = true; edge_node = nullptr;
		}else if (down_key_down && !restrict_input_y) {
			//if the down key is down then change moves, reset gravity and let go of the edge
			gravity = 0;
			update_move(moves.JUMP, 10, false);
			grabbing_edge = false;
			edge_node->edgeempty = true; edge_node = nullptr;
		}
	}

	/**
	------------------------------------------------------------------------------------------
								GRAVITY + Y COLLIDE + JUMP
	------------------------------------------------------------------------------------------
	**/
	//apply gravity and collide_ downwards and upwards with solid tiles
	floor_collided = false;
	if (!grabbing_edge) {
		if (gravity > 0) {
			//if the gravity is greater than 0, try colliding downwards
			if ((node = Collision::collide_down(coords.x, coords.y)) && node->solid) {
				//snap to bottom tile and reset variables
				rotation = 0;
				gravity = 0;
				pos.y = (int)coords.y * 32;
				double_jump = false;
				floor_collided = true;
				//if not doing other actions, idle if speed is low and start running if the speed is fast
				if (current_move != moves.JUMP && current_move != moves.EDGE_GRAB) {
					if (current_move != moves.CROUCH || 
						(current_move == moves.CROUCH && !down_key_down)) {
						if (speed_x >= 1 || speed_x <= -1) {
							update_move(moves.RUN, 15, true);
						}else if (current_move != moves.LAND) {
							update_move(moves.IDLE, 5, true);
						}
					}
				}

				//change to idle after the landing animation has finished
				if (animator->paused && current_move == moves.LAND) { update_move(moves.IDLE, 5, true); }
				//play the landing animation after jumping or landing
				if (current_move == moves.JUMP || current_move == moves.LAND) {
					update_move(moves.LAND, 10, false);
				}
			}

			//change the move to jump when walked off solid platform
			if (!floor_collided) {
				if (current_move == moves.IDLE || current_move == moves.RUN ||
					current_move == moves.CROUCH || current_move == moves.DASH_ATTACK ||
					current_move == moves.SLIDE_ATTACK) {
					update_move(moves.JUMP, 10, false);
				}
			}
		}

		//limit gravity to the max fall speed
		gravity += fall_speed;
		if (gravity >= max_fall_speed) { gravity = max_fall_speed; }

		//if the gravity is less than 0 and colliding up with a solid tile, then snap to the tile
		if (gravity < 0 && (node = Collision::collide_up(coords.x, coords.y)) && node->solid) {
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
	if (floor_collided) {
		if (!up_key_pressed && up_key_down && !restrict_input_y) {
			gravity = -jump_height / 8;
			up_key_pressed = true;
			holding_jump = true;
			update_move(moves.JUMP, 10, false);
		}
	}

	//double jumps and hold for higher jumps
	if (up_key_down && !restrict_input_y) {
		//if the up key is down after jumping once then apply a double jump
		if (!up_key_pressed && !double_jump) {
			gravity = -jump_height / 8;
			holding_jump = true;
			double_jump = true;
			up_key_pressed = true;
			update_move(moves.DOUBLE_JUMP, 15, false);
		}
		//makes jump longer as long as up key is down or until the jump height limit is reached
		if (holding_jump) {
			gravity -= fall_speed * 4;
			if (gravity <= -jump_height) {
				holding_jump = false;
			}
		}
	}

	//apply rotation to double jump depending on direction
	if (current_move == moves.DOUBLE_JUMP) {
		if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { rotation -= 40; }else { rotation += 40; }
	}else if (current_move == moves.JUMP && gravity > 0) {
		update_move(moves.AIR_LAND, 4, false);
	}

	/**
	------------------------------------------------------------------------------------------
										PUNCH ATTACK CYCLE
	------------------------------------------------------------------------------------------
	**/
	//if the a key is pressed while idling or running, cycle between punch, kick and rapid punch
	if (current_move != moves.DASH_ATTACK && current_move != moves.CROUCH) {
		if (current_move == moves.IDLE || (current_move == moves.RUN && 
			!right_key_down && !left_key_down)) {
			if (a_key_down) {
				if (!a_key_pressed) {
					if ((punch_cycle == moves.KICK || punch_cycle == moves.RAPID_PUNCH) && 
						punch_timer <= PUNCH_CYCLE_TIME) {
						//change move to rapid punch
						update_move(moves.RAPID_PUNCH, 15, false, true);
						punch_cycle = moves.RAPID_PUNCH;
						base_parent->dealt_damage = false;
					}else if (punch_cycle == moves.PUNCH && punch_timer <= PUNCH_CYCLE_TIME) {
						//change move to kick
						update_move(moves.KICK, 15, false, true);
						punch_cycle = moves.KICK;
						base_parent->dealt_damage = false;
					}else {
						//change move to punch
						update_move(moves.PUNCH, 10, false, true);
						punch_cycle = moves.PUNCH;
						base_parent->dealt_damage = false;
					}
					//restrict movement input and reset punch timer
					punch_timer = 0;
					restrict_input_x = true;
					restrict_input_y = true;
					a_key_pressed = true;
					punching = true;
				}
			}
		}
	}

	//increment punch_timer and allow movement input after a move in the punch cycle has been performed
	if (punching && !lock_move_update) {
		restrict_input_x = false; restrict_input_y = false;
		punching = false;
		update_move(moves.IDLE, 5, true);
	}else {
		++punch_timer;
		if (punch_timer >= PUNCH_CYCLE_TIME) { punch_timer = 0; punch_cycle = moves.IDLE; }
	}

	/**
	------------------------------------------------------------------------------------------
										RUN + DASH ATTACK
	------------------------------------------------------------------------------------------
	**/
	//if the dash attack is not on cooldown then perform a dash attack when the a is pressed
	if (!dashing) { ++dash_cooldown_timer; }
	if (current_move == moves.RUN && dash_cooldown_timer >= DASH_COOLDOWN) {
		if (a_key_down) {
			if (!a_key_pressed) {
				//apply force depending on flip direction
				if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { force_x += 10; }else { force_x -= 10; }
				//update movement and restrict movement input
				update_move(moves.DASH_ATTACK, 10, false, true);
				restrict_input_x = true;
				restrict_input_y = true;
				a_key_pressed = true;
				base_parent->dealt_damage = false;
				dashing = true;
				dash_cooldown_timer = 0;
			}
		}
	}
	//if dashing and slowed down then end dash and allow movement input
	if (dashing && speed_x <= 2 && speed_x >= -2 && !lock_move_update) {
		restrict_input_x = false; restrict_input_y = false; dashing = false; animator->paused = false;
		update_move(moves.IDLE, 5, true);
	}

	/**
	------------------------------------------------------------------------------------------
										CROUCH SLIDE ATTACK
	------------------------------------------------------------------------------------------
	**/
	//if the down key is down then change the move to crouch
	if (floor_collided) {
		if (down_key_down && !down_key_pressed) {
			if (!restrict_input_y && current_move != moves.SLIDE_ATTACK) {
				update_move(moves.CROUCH, 5, false);
			}
		}
	}

	//if the slide attack is not on cooldown then perform a slide attack when the a is pressed
	if (!sliding) { ++sliding_cooldown_timer; }
	if (current_move == moves.CROUCH && sliding_cooldown_timer >= SLIDE_COOLDOWN) {
		if (a_key_down && down_key_down) {
			if (!a_key_pressed && !down_key_pressed) {
				//apply force depending on flip direction
				if (flip == SDL_RendererFlip::SDL_FLIP_NONE) { force_x += 8; }else { force_x -= 8; }
				//update movement and restrict movement input
				update_move(moves.SLIDE_ATTACK, 10, false, true);
				restrict_input_x = true;
				restrict_input_y = true;
				a_key_pressed = true;
				down_key_pressed = true;
				sliding = true;
				base_parent->dealt_damage = false;
				sliding_cooldown_timer = 0;
				speed_x += force_x;
			}
		}
	}
	//if sliding and slowed down then end slide and allow movement input
	if (sliding && speed_x <= 1 && speed_x >= -1 && !lock_move_update) {
		restrict_input_x = false; restrict_input_y = false; sliding = false; animator->paused = false;
		update_move(moves.IDLE, 5, true);
	}

	/**
	------------------------------------------------------------------------------------------
											DOWN AIR KICK
	------------------------------------------------------------------------------------------
	**/
	if (!floor_collided && down_key_down && !down_key_pressed && a_key_down && !a_key_pressed && 
		!double_jump && !restrict_input_y) {
		update_move(moves.AIR_DOWN_KICK, 15, false, true);
		down_key_pressed = true;
		a_key_pressed = true;
		restrict_input_x = true;
		restrict_input_y = true;
		down_air_kick = true;
		base_parent->dealt_damage = false;
	}
	if (down_air_kick && !lock_move_update) {
		update_move(moves.JUMP, 10, false);
		double_jump = false;
		restrict_input_x = false;
		restrict_input_y = false;
		down_air_kick = false;
	}

	/**
	------------------------------------------------------------------------------------------
											RIGHT AIR KNEE
	------------------------------------------------------------------------------------------
	**/
	if (!floor_collided && a_key_down && !a_key_pressed && !double_jump && !restrict_input_y &&
		((flip == SDL_RendererFlip::SDL_FLIP_NONE && right_key_down) || 
		(flip == SDL_RendererFlip::SDL_FLIP_HORIZONTAL && left_key_down))) {
		update_move(moves.AIR_KNEE, 15, false, true);
		restrict_input_x = true;
		restrict_input_y = true;
		right_air_knee = true;
		a_key_pressed = true;
		base_parent->dealt_damage = false;
	}
	if (right_air_knee && !lock_move_update) {
		update_move(moves.JUMP, 10, false);
		double_jump = false;
		restrict_input_x = false;
		restrict_input_y = false;
		right_air_knee = false;
	}

	/**
	------------------------------------------------------------------------------------------
											AIR SOMERSAULT
	------------------------------------------------------------------------------------------
	**/
	if (!floor_collided && up_key_down && !down_key_pressed && a_key_down && !a_key_pressed && 
		!restrict_input_y && !air_somersault) {
		update_move(moves.AIR_SOMERSAULT, 10, false, true);
		restrict_input_x = true;
		restrict_input_y = true;
		a_key_pressed = true;
		up_key_down = true;
		air_somersault = true;
		base_parent->dealt_damage = false;
		rotation = 0;
	}
	if (air_somersault && !lock_move_update) {
		update_move(moves.JUMP, 10, false);
		restrict_input_x = false;
		restrict_input_y = false;
		air_somersault = false;
	}

	/**
	------------------------------------------------------------------------------------------
											RIGHT AIR KICK
	------------------------------------------------------------------------------------------
	**/
	if (!floor_collided && a_key_down && !a_key_pressed && !double_jump && !restrict_input_y && 
		!right_key_down && !left_key_down && !up_key_down) {
		update_move(moves.AIR_KICK, 12, false);
		restrict_input_x = true;
		restrict_input_y = true;
		a_key_pressed = true;
		right_air_kick = true;
		base_parent->dealt_damage = false;
	}
	if (right_air_kick) {
		if (animator->paused || current_move != moves.AIR_KICK) {
			update_move(moves.JUMP, 10, false);
			double_jump = false;
			restrict_input_x = false;
			restrict_input_y = false;
			right_air_kick = false;
		}
	}

	/**
	------------------------------------------------------------------------------------------
										APPLY VALUES
	------------------------------------------------------------------------------------------
	**/
	//set keyboard keys to false when they aren't being pressed
	if (!a_key_down) { a_key_pressed = false; }
	if (!down_key_down) { down_key_pressed = false; }
	if (!up_key_down) { up_key_pressed = false; holding_jump = false; }

	//apply force friction to force_x
	force_x = force_x * FORCE_FRICTION;

	//apply speedx and gravity to the position
	pos.x += speed_x;
	pos.y += gravity;
	//apply force_x to the position
	pos.x += force_x;

	//if the animation is locked and has looped once then unlock it
	if (lock_move_update && animator->paused) {
		lock_move_update = false;
		if (current_move == moves.HIT) {
			if (!floor_collided) { update_move(moves.JUMP, 10, false); }
			restrict_input_x = false;
			restrict_input_y = false;
		}
	}

	//update the animator
	animator->update();
}

/**
changes the current move to a new move and updates the animation
**/
void Movement::update_move(int newmove, int fps, bool loop, bool lock) {
	if (current_move != newmove) {
		if (!lock_move_update || lock) {
			current_move = newmove;
			animation_sheet = base_universe->assets->fighter_sheets[0];
			animator->update_texture(animation_sheet, 64, 64, moves.move_frames[current_move], 1);
			animator->set_fps(fps);
			animator->loop = loop;
			animator->paused = false;
			src_rect.y = current_move * 64;
			lock_move_update = lock;
		}
	}
}

/**
adds force in positive or negative direction depending on flip parameter
**/
void Movement::add_flip_force(SDL_RendererFlip newflip, float forcemultiplierx, float forcemultipliery) {
	if (newflip == SDL_RendererFlip::SDL_FLIP_NONE) {
		add_force(forcemultiplierx, forcemultipliery);
		flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
	}else {
		add_force(-forcemultiplierx, forcemultipliery);
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
	}
}

/**
adds force depending on health
**/
void Movement::add_force(float forcemultiplierx, float forcemultipliery) {
	force_x += ((base_parent->health / 100.f) + 1) * forcemultiplierx;
	gravity -= ((base_parent->health / 100.f) + 1) * forcemultipliery;
	if (grabbing_edge) {
		grabbing_edge = false; edge_node->edgeempty = true; edge_node = nullptr; update_move(moves.JUMP, 10, false);
	}
	update_move(moves.HIT, 5, false, true);
	restrict_input_x = true;
	restrict_input_y = true;
}