#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../moves/CaptainFalcon.h"
#include "../../../tools/Point2DF.h"
#include "../../../tools/Animator.h"
#include "../../../managers/Texture.h"
#include "../../../map/Node.h"
#include "FighterBase.h"

class Movement : FighterBase {

	public:
		Movement(Fighter* parent);

		//position
		Point2DF pos;
		Point2DF coords;

		//animation
		SDL_RendererFlip flip;

		//movement
		float gravity;
		float speed_x;

		//moves
		Moves moves;
		int current_move;

		//input
		bool up_key_pressed = false;
		bool down_key_pressed = false;
		bool a_key_pressed = false;

		bool left_key_down = false;
		bool right_key_down = false;
		bool up_key_down = false;
		bool down_key_down = false;
		bool a_key_down = false;
		bool b_key_down = false;

		//force
		float force_x;
		const float FORCE_FRICTION = .95f;

		/**
		updates the movement
		**/
		void update_movement();

		/**
		adds force in positive or negative direction depending on flip parameter
		**/
		void add_flip_force(SDL_RendererFlip new_flip, 
			float force_multiplier_x, float force_multiplier_y);

		/**
		adds force depending on health
		**/
		void add_force(float force_multiplier_x, float force_multiplier_y);

	private:
		//movement restrictions
		bool restrict_input_x;
		bool restrict_input_y;

		//movement values
		float move_speed = 1.2f;
		float max_speed = 12;
		float friction = .92f;
		float jump_height = 8;
		float fall_speed = .4f;
		float max_fall_speed = 10;

		//jumping
		bool double_jump;
		bool holding_jump;

		//edge grab
		bool grabbing_edge;
		Node* edge_node;

		//punching
		int punch_timer;
		int punch_cycle;
		const int PUNCH_CYCLE_TIME = 20;
		bool punching;

		//dash attack
		bool dashing;
		int dash_cooldown_timer;
		const int DASH_COOLDOWN = 25;

		//slide attack
		bool sliding;
		int sliding_cooldown_timer;
		const int SLIDE_COOLDOWN = 25;

		//air kicks
		bool down_air_kick;
		bool right_air_knee;
		bool air_somersault;
		bool right_air_kick;

		//collision
		bool floor_collided;
		bool right_collided;
		bool left_collided;

		//animation
		bool lock_move_update;

		/**
		changes the current move to a new move and updates the animation
		**/
		void update_move(int new_move, int fps, bool loop = true, bool lock = false);

	protected:
		//rendering
		SDL_Rect rect;
		SDL_Rect src_rect;

		//animation
		Animator* animator;
		Texture* animation_sheet;
		SDL_Point origin;
		float rotation;
};

#endif