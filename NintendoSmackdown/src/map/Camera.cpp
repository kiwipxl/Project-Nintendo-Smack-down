#include "Camera.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
};

Camera::Camera() {
	reset();
}

void Camera::update() {
	int min = INT_MAX;
	int max = -INT_MAX;
	for (Fighter* f : universe->entitymanager->fighters) {
		if (f->pos.x < min) { min = f->pos.x; }
		if (f->pos.x > max) { max = f->pos.x; }
	}
	int difx = (min + ((max - min) / 2)) - universe->winmanager->centerx;
	x -= (x + difx) / MOVE_SMOOTHING;
	scale -= (scale - (1 + ((((min + universe->winmanager->centerx) - max)) / ZOOM))) / ZOOM_SMOOTHING;

	gridsize = 32 * scale;
}

void Camera::reset() {
	x = 0; y = 0;
	scale = 1;
}

float Camera::getoffsetx(float posx) {
	return -(scale - 1) * (universe->winmanager->centerx - posx);
}

float Camera::getoffsety(float posy) {
	return -(scale - 1) * (universe->winmanager->centery - posy);
}