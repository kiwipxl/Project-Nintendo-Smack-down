#include "Particles.h"
#include <iostream>

Particles::Particles(ParticleEmitter* emitter) : ParticleRenderer(), ParticleEmitter(*emitter) {
	std::cout << "particle emitter: " << spawn_x << "\n";
	set_emitter_parent(this);
	set_renderer_parent(this);
}

void Particles::update() {
	update_emitter();
	update_renderer();
}