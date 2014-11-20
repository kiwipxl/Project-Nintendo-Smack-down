#include "Collision.h"
#include <iostream>
#include "Map.h"

class Universe {

	public:
		static Map* map;
};

Node* Collision::collideright(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->gridwidth - 2 && y < universe->map->gridheight - 1) {
		if (universe->map->nodes[x + 1.5f][y + 1]->solid) {
			return universe->map->nodes[x + 1.5f][y + 1];
		}else if (universe->map->nodes[x + 1.5f][y]->solid) {
			return universe->map->nodes[x + 1.5f][y];
		}
	}
	return NULL;
}

Node* Collision::collideleft(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->gridwidth - 1 && y < universe->map->gridheight - 1) {
		if (universe->map->nodes[x][y + 1]->solid) {
			return universe->map->nodes[x][y + 1];
		}else if (universe->map->nodes[x][y]->solid) {
			return universe->map->nodes[x][y];
		}
	}
	return NULL;
}

Node* Collision::collideup(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->gridwidth - 2 && y < universe->map->gridheight - 1) {
		if (universe->map->nodes[x + .6f][y]->solid) {
			return universe->map->nodes[x + .6f][y];
		}else if (universe->map->nodes[x + 1.4f][y]->solid) {
			return universe->map->nodes[x + 1.4f][y];
		}
	}
	return NULL;
}

Node* Collision::collidedown(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->gridwidth - 2 && y < universe->map->gridheight - 2) {
		if (universe->map->nodes[x + 1][y + 2]->solid) {
			return universe->map->nodes[x + 1][y + 2];
		}else if (universe->map->nodes[x + 1.2f][y + 2]->solid) {
			return universe->map->nodes[x + 1.2f][y + 2];
		}else if (universe->map->nodes[x + .8f][y + 2]->solid) {
			return universe->map->nodes[x + .8f][y + 2];
		}
	}
	return NULL;
}