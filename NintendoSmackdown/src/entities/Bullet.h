#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "../tools/Point2DF.h"

class Tank;

class Bullet : Universal {

	public:
		Bullet(int x, int y, float rotation);

		Point2DF pos;
		SDL_Rect rect;
		bool removed;
		Tank* tank;
		Tank* closesttank;

		void update();
		void render();

	private:
		float speedx;
		float speedy;
		int removetimer;
};

#endif