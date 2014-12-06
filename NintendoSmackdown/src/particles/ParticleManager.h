#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "Particles.h"
#include <vector>

class ParticleManager {

	public:
		ParticleManager();

		std::vector<Particles*> particles;

		void update();

		Particles* create_particle(ParticleEmitter* emitter);
};

#endif