#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2DF.h"

class Item : Universal {

	public:
		Item(int x, int y);

		Point2DF pos;
		SDL_Rect rect;

		void update();
		void render();
};

#endif