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
		int map_width_scaled;
		int map_height_scaled;
		vector<vector<Node*>> nodes;

		vector<int> fighter_types;
		vector<int> player_ids;

		void create();
		void update();
		void remove();
		void resize_update(int w = 0, int h = 0);

	private:
		//map renderering
		SDL_Rect rect;
		SDL_Rect src_rect;

		//background rendering
		SDL_Rect bgrect;
		SDL_Rect bgsrc_rect;
};

#endif