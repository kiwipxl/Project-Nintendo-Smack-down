#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL.h>
#include <vector>
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

class Fighter : Universal {

	public:
		Fighter(int x, int y);

		Point2DF pos;
		Point2DF coords;

		void update();

	private:
		SDL_Rect rect;
		SDL_Rect srcrect;
		Animator* animator;
		Texture fightersheet;
		SDL_RendererFlip flip;
		SDL_Point origin;
		Move move;

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

		Node* collideright(float x, float y);
		Node* collideleft(float x, float y);
		Node* collideup(float x, float y);
		Node* collidedown(float x, float y);

		bool lockmoveupdate;

		void updatemove(Move newmove, int fps, bool loop = true, bool lock = false);
};

#endif