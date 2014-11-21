#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../tools/Universal.h"
#include "../tools/Point2DF.h"
#include "../tools/Animator.h"
#include "../managers/Texture.h"
#include "../map/Node.h"
#include "moves/CaptainFalcon.h"

class Movement : public Universal {

	public:
		Movement();

		//position
		Point2DF pos;
		Point2DF coords;

		//rendering
		SDL_Rect rect;
		SDL_Rect srcrect;

		//animation
		Animator* animator;
		Texture* animationsheet;
		SDL_RendererFlip flip;
		SDL_Point origin;
		float rotation;

		//moves
		Moves moves;
		int currentmove;

		/**
		updates the movement
		**/
		void updatemovement();

	private:
		//movement
		float gravity;
		float speedx;
		float speedy;
		bool restrictinputx;
		bool restrictinputy;

		//movement values
		float movespeed = 1.2f;
		float maxspeed = 12;
		float friction = .92f;
		float jumpheight = 10;
		float fallspeed = .55f;
		float maxfallspeed = 10;

		//jumping
		bool doublejump;
		bool holdingjump;

		//edge grab
		bool grabbingedge;

		//punching
		int punchtimer;
		int punchcycle;
		const int PUNCHCYCLETIME = 20;

		//force
		float forcex;
		float forcey;
		const float FORCEFRICTION = .9f;

		//dash attack
		bool dashing;
		int dashcooldowntimer;
		const int DASHCOOLDOWN = 25;

		//slide attack
		bool sliding;
		int slidingcooldowntimer;
		const int SLIDECOOLDOWN = 25;

		//collision
		bool floorcollided;
		bool rightcollided;
		bool leftcollided;

		//input
		bool upkeypressed;
		bool downkeypressed;
		bool akeypressed;

		//animation
		bool lockmoveupdate;

		/**
		changes the current move to a new move and updates the animation
		**/
		void updatemove(int newmove, int fps, bool loop = true, bool lock = false);
};

#endif