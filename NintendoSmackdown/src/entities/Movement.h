#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "../tools/Universal.h"
#include "../tools/Point2DF.h"
#include "../tools/Animator.h"
#include "../managers/Texture.h"
#include "../map/Node.h"

enum Move {
	IDLE,
	IDLE2,
	JUMP,
	LAND,
	KICKA,
	PUNCHA,
	ROLL,
	RUNNING,
	SHIELD
};

class Movement : public Universal {

	public:
		Movement();

		Point2DF pos;
		Point2DF coords;

		SDL_Rect rect;
		SDL_Rect srcrect;
		Animator* animator;
		Texture animationsheet;
		SDL_RendererFlip flip;
		SDL_Point origin;
		Move move;

		float rotation;

		void updatemovement();

	private:
		float gravity;
		float speedx;
		float speedy;

		float movespeed = .75f;
		float maxspeed = 15;
		float friction = .92f;
		float jumpheight = 10;
		float fallspeed = .55f;
		float maxfallspeed = 10;

		bool jumped;
		bool doublejumped;
		bool holdingjump;

		bool lockmoveupdate;

		void updatemove(Move newmove, int fps, bool loop = true, bool lock = false);
};

#endif