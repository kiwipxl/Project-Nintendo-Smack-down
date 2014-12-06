#include "ParticleManager.h"
#include <iostream>

ParticleManager::ParticleManager() {

}

Particles* ParticleManager::create_particle(ParticleEmitter* emitter) {
	Particles* p = new Particles(emitter);
	particles.push_back(p);
	return p;
}

void ParticleManager::update() {
	for (Particles* &p : particles) {
		p->update();
	}
}