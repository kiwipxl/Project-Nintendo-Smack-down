#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"
#include "Node.h"

class Map : Universal {

	public:
		Map();

		//map
		bool created;
		int grid_width;
		int grid_height;
		int map_width;
		int map_height;
		vector<vector<Node*>> nodes;

		void create();
		void update();
		void remove();

	private:
		//map renderering
		SDL_Rect rect;
		SDL_Rect src_rect;

		//background rendering
		SDL_Rect bgrect;
		SDL_Rect bgsrc_rect;
};

#endif