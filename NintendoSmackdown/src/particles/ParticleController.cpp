#include "ParticleController.h"
#include <iostream>

ParticleController::ParticleController(ParticleEmitter* emitter, ParticleType c_type) 
	: ParticleRenderer(), ParticleEmitter(*emitter) {
	set_emitter_parent(this);
	set_renderer_parent(this);
	type = c_type;
	create_texture();
}

void ParticleController::update() {
	update_emitter();
	update_renderer();

	if (particles.size() == 0 && spawned && spawn_once) {
		removed = true;
		delete texture;
	}
}

void ParticleController::create_particle(int spawn_x, int spawn_y) {
	if (particles.size() < max_particles) {
		Particle* p = new Particle(texture->width, texture->height, spawn_x, spawn_y, type);
		p->v_id = particles.size() * 4;
		particles.push_back(p);
	}
}