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
	//scalex = 1.2f + ((((min + universe->winmanager->centerx) - max) / 2) / 500.f);
	//scaley = scalex;
	
	if (scale <= 2) { scale += .001f; }

	gridsize = 32 * scale;
}

void Camera::reset() {
	x = 0; y = 0;
	scale = 1;
}

float Camera::getscaleoffsetx(int width) {
	return -((scale - 1) * width) / 2.f;
}

float Camera::getscaleoffsety(int height) {
	return -((scale - 1) * height) / 2.f;
}