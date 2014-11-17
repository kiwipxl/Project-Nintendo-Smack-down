#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class Map : Universal {

	public:
		Map();

		void create();
		void update();
		void remove();

	private:
		bool created;
};

#endif