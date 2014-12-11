#include "ParticleManager.h"
#include <iostream>
#include <algorithm>

ParticleManager::ParticleManager() {

}

ParticleController* ParticleManager::create_particle_chunk(ParticleEmitter* emitter, ParticleType type) {
	ParticleController* p = new ParticleController(emitter, type);
	particle_chunks.push_back(p);
	return p;
}

void ParticleManager::update() {
	particles_uploaded = 0;
	particles_drawn = 0;
	for (ParticleController* &p : particle_chunks) {
		particles_uploaded += p->max_particles;
		p->update();
		if (p->removed) { p = nullptr; }
	}

	particle_chunks.erase(std::remove(particle_chunks.begin(), particle_chunks.end(), nullptr), particle_chunks.end());
}