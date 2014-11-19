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

		bool created;
		int gridwidth;
		int gridheight;
		vector<vector<Node*>> nodes;

		void create();
		void update();
		void remove();

	private:
		SDL_Rect rect;
		SDL_Rect srcrect;
};

#endif