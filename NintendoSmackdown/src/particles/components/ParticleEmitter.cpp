#include "ParticleEmitter.h"
#include <iostream>
#include "../ParticleController.h"

ParticleEmitter::ParticleEmitter(int c_spawn_x, int c_spawn_y, int c_spawn_rate, 
								 int c_spawn_amount, int c_max_particles, bool c_spawn_once) {
	spawn_x = c_spawn_x; spawn_y = c_spawn_y;
	spawn_rate = c_spawn_rate;
	spawn_amount = c_spawn_amount;
	spawn_once = c_spawn_once;
	spawn_timer = 0;
	max_particles = c_max_particles;
	spawned = false;
}

void ParticleEmitter::update_emitter() {
	if (!spawn_once || !spawned) {
		++spawn_timer;
		if (spawn_timer >= spawn_rate) {
			spawn_timer = 0;
			for (int n = 0; n < spawn_amount; ++n) {
				parent->create_particle(spawn_x, spawn_y);
			}
			spawned = true;
		}
	}
}