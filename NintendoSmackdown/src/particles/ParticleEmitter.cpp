#include "ParticleEmitter.h"
#include <iostream>

ParticleEmitter::ParticleEmitter(int c_spawn_x, int c_spawn_y, int c_spawn_rate, 
								 int c_spawn_amount, bool c_spawn_once) {
	spawn_x = c_spawn_x; spawn_y = c_spawn_y;
	spawn_rate = c_spawn_rate;
	spawn_amount = c_spawn_amount;
	spawn_once = c_spawn_once;
	spawn_timer = 0;
	spawned = false;
}

void ParticleEmitter::update_emitter() {
	++spawn_timer;
	if (spawn_timer >= spawn_rate) {
		spawn_timer = 0;
	}
}