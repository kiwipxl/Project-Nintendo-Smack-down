#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2DF.h"
#include "../tools/Animator.h"

class Fighter : Universal {

	public:
		Fighter(int x, int y);

		Point2DF pos;
		SDL_Rect rect;
		SDL_Rect srcrect;
		Animator* animator;

		void update();
		void render();
};

#endif