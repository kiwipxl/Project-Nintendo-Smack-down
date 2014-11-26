#include "Camera.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../map/Map.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static Map* map;
};

Camera::Camera() {
	reset();
}

void Camera::update() {
	minboundsx = -200;
	maxboundsx = universe->map->mapwidth;
	minboundsy = 0;
	maxboundsy = universe->map->mapheight;

	int minx = INT_MAX;
	int maxx = -INT_MAX;
	int miny = INT_MAX;
	int maxy = -INT_MAX;
	for (Fighter* f : universe->entitymanager->fighters) {
		if (f->pos.x < minx) { minx = f->pos.x; }
		if (f->pos.x > maxx) { maxx = f->pos.x; }
		if (f->pos.y < miny) { miny = f->pos.y; }
		if (f->pos.y > maxy) { maxy = f->pos.y; }
	}
	if (minx < minboundsx) { minx = minboundsx; } if (maxx > maxboundsx) { maxx = maxboundsx; }
	if (miny < minboundsy) { miny = minboundsy; } if (maxy > maxboundsy) { maxy = maxboundsy; }

	int difx = (minx + ((maxx - minx) / 2) - (universe->winmanager->centerx - 64)) * scale;
	int dify = (miny + ((maxy - miny) / 2) - (universe->winmanager->centery - 64)) * (scale / 2);
	x -= (x + difx) / MOVE_SMOOTHING;
	y -= (y + dify) / MOVE_SMOOTHING;
	scale -= (scale - (1 + ((((minx + universe->winmanager->centerx) - maxx)) / ZOOM))) / ZOOM_SMOOTHING;
	if (scale > MAX_ZOOM) { scale = MAX_ZOOM;
	}else if (scale < MIN_ZOOM) { scale = MIN_ZOOM; }

	gridsize = 32 * scale;
}

void Camera::reset() {
	x = 0; y = 0;
	scale = 1;
	minboundsx = 0; maxboundsx = 0;
	minboundsy = 0; maxboundsy = 0;
}

float Camera::getoffsetx(float posx) {
	return -(scale - 1) * (universe->winmanager->centerx - posx);
}

float Camera::getoffsety(float posy) {
	return -(scale - 1) * (universe->winmanager->centery - posy);
}