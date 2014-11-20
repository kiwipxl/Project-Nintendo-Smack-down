#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL.h>
#include "Movement.h"

class Fighter : Movement {

	public:
		Fighter(int x, int y);

		void update();
};

#endif