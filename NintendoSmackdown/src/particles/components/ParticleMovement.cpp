#include "ParticleMovement.h"
#include <iostream>
#include "../Particle.h"
#include "../../managers/WindowManager.h"
#include "../../map/Camera.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Camera* camera;
};

ParticleMovement::ParticleMovement(int c_spawn_x, int c_spawn_y) {
	spawn_x = c_spawn_x;
	spawn_y = c_spawn_y;
}

void ParticleMovement::initiate_movement() {
	remove_rate = 50 + (rand() % 100);
	switch (parent->type) {
		case CLOUD:
			speedx = ((rand() / (float)RAND_MAX) - (rand() / (float)RAND_MAX)) * 15;
			gravity = ((rand() / (float)RAND_MAX) - (rand() / (float)RAND_MAX)) * 10;
			parent->scale = .1f + ((rand() / (float)RAND_MAX) / 2);
			break;
		case BLOOD:
			speedx = ((rand() / (float)RAND_MAX) - (rand() / (float)RAND_MAX)) * 5;
			gravity = -5 - ((rand() / (float)RAND_MAX) * 5);
			parent->scale = .1f + ((rand() / (float)RAND_MAX) / 2);
			remove_rate = 50 + (rand() % 20);
			break;
	}
}

void ParticleMovement::update_movement() {
	++remove_timer;
	if (remove_timer >= remove_rate || parent->scale <= 0) {
		remove_timer = 0;
		removed = true;
		return;
	}else if (parent->type != BLOOD && remove_timer >= remove_rate - 50) {
		parent->scale -= .01f;
	}

	switch (parent->type) {
		case CLOUD:
			speedx = speedx * .97f;
			gravity = gravity * .98f;
			break;
		case BLOOD:
			speedx = speedx * .97f;

			gravity += .5f;
			if (gravity >= 10) { gravity = 10; }
			break;
	}

	accel.x += speedx;
	accel.y += gravity;
	
	pos.x = spawn_x + accel.x;
	pos.y = spawn_y + accel.y;
	pos.x += universe->camera->x + universe->camera->get_offset_x(pos.x);
	pos.y += universe->camera->y + universe->camera->get_offset_y(pos.y);
}