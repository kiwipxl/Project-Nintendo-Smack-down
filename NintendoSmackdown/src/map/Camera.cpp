#include "Camera.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../map/Map.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static EntityManager* entity_manager;
		static Map* map;
};

Camera::Camera() {
	reset();
}

void Camera::update() {
	int min_x = INT_MAX;
	int max_x = -INT_MAX;
	int min_y = INT_MAX;
	int max_y = -INT_MAX;
	bool set_boundaries = false;
	for (Fighter* f : universe->entity_manager->fighters) {
		if (!f->respawning) {
			if (f->pos.x < min_x) { min_x = f->pos.x; }
			if (f->pos.x > max_x) { max_x = f->pos.x; }
			if (f->pos.y < min_y) { min_y = f->pos.y; }
			if (f->pos.y > max_y) { max_y = f->pos.y; }
			set_boundaries = true;
		}
	}
	if (!set_boundaries) {
		min_x = 0;
		max_x = universe->map->map_width;
		min_y = 0;
		max_y = universe->map->map_height;
	}

	if (min_x < min_bounds_x) { min_x = min_bounds_x; } if (max_x > max_bounds_x) { max_x = max_bounds_x; }
	if (min_y < min_bounds_y) { min_y = min_bounds_y; } if (max_y > max_bounds_y) { max_y = max_bounds_y; }

	int dif_x = (min_x + ((max_x - min_x) / 2) - (universe->win_manager->center_x - 32)) * scale;
	int dif_y = (min_y + ((max_y - min_y) / 2) - (universe->win_manager->center_y - 64)) * scale;
	x -= (x + dif_x) / MOVE_SMOOTHING;
	y -= (y + dif_y) / MOVE_SMOOTHING;
	scale -= (scale - (1 + ((((min_x + universe->win_manager->center_x) - max_x)) / ZOOM))) / ZOOM_SMOOTHING;
	if (scale > MAX_ZOOM) { scale = MAX_ZOOM;
	}else if (scale < MIN_ZOOM) { scale = MIN_ZOOM; }

	grid_size = 32 * scale;
}

void Camera::reset() {
	x = 0; y = 0;
	scale = 1;
	min_bounds_x = 0;
	max_bounds_x = universe->map->map_width - 128;
	min_bounds_y = 0;
	max_bounds_y = universe->map->map_height;
}

float Camera::get_offset_x(float pos_x) {
	return -(scale - 1) * (universe->win_manager->center_x - pos_x);
}

float Camera::get_offset_y(float pos_y) {
	return -(scale - 1) * (universe->win_manager->center_y - pos_y);
}