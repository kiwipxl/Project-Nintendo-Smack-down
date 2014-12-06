#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../moves/CaptainFalcon.h"
#include "../../../tools/Point2DF.h"
#include "../../../tools/Animator.h"
#include "../../../renderer/Texture.h"
#include "../../../map/Node.h"
#include "../../../input/InputManager.h"
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
		Key* left_key;
		Key* right_key;
		Key* up_key;
		Key* down_key;
		Key* a_key;
		Key* b_key;

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
		float move_speed = 1;
		float max_speed = 10;
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
		const int PUNCH_CYCLE_TIME = 40;
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

	protected:
		//rendering
		SDL_Rect rect;
		SDL_Rect src_rect;

		//animation
		Animator* animator;
		SDL_Point origin;
		float rotation;

		/**
		changes the current move to a new move and updates the animation
		**/
		void update_move(int new_move, int fps, bool loop = true, bool lock = false);
};

#endif