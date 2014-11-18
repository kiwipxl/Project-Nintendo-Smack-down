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

		void create();
		void update();
		void remove();

	private:
		bool created;
		int gridwidth;
		int gridheight;
		vector<vector<Node*>> nodes;
		SDL_Rect rect;
		SDL_Rect srcrect;
};

#endif