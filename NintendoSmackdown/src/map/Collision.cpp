#include "Collision.h"
#include <iostream>
#include "Map.h"

class Universe {

	public:
		static Map* map;
};

Node* Collision::collide_right(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->grid_width - 2 && y < universe->map->grid_height - 1) {
		if (universe->map->nodes[x + 1.5f][y + 1]->solid) {
			return universe->map->nodes[x + 1.5f][y + 1];
		}else if (universe->map->nodes[x + 1.5f][y]->solid) {
			return universe->map->nodes[x + 1.5f][y];
		}
	}
	return NULL;
}

Node* Collision::collide_left(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->grid_width - 1 && y < universe->map->grid_height - 1) {
		if (universe->map->nodes[x + .4f][y + 1]->solid) {
			return universe->map->nodes[x + .4f][y + 1];
		}else if (universe->map->nodes[x + .4f][y]->solid) {
			return universe->map->nodes[x + .4f][y];
		}
	}
	return NULL;
}

Node* Collision::collide_up(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->grid_width - 2 && y < universe->map->grid_height - 1) {
		if (universe->map->nodes[x + .6f][y]->solid) {
			return universe->map->nodes[x + .6f][y];
		}else if (universe->map->nodes[x + 1.4f][y]->solid) {
			return universe->map->nodes[x + 1.4f][y];
		}
	}
	return NULL;
}

Node* Collision::collide_down(float x, float y) {
	if (x >= 0 && y >= 0 && x < universe->map->grid_width - 2 && y < universe->map->grid_height - 2) {
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