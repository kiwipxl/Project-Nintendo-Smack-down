#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include "ParticleController.h"
#include "ParticleManager.h"
#include <vector>

class ParticleManager {

	public:
		ParticleManager();

		std::vector<ParticleController*> particle_chunks;
		int particles_uploaded = 0;
		int particles_drawn = 0;

		void update();

		ParticleController* create_particle_chunk(ParticleEmitter* emitter, ParticleType type);
};

#endif