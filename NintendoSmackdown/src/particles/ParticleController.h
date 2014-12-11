#ifndef PARTICLE_CONTROLLER_H
#define PARTICLE_CONTROLLER_H

#include "components/ParticleEmitter.h"
#include "components/ParticleRenderer.h"
#include "Particle.h"
#include <vector>

class ParticleController : public ParticleRenderer, public ParticleEmitter {

	public:
		ParticleController(ParticleEmitter* emitter, ParticleType c_type);

		std::vector<Particle*> particles;
		ParticleType type;
		bool removed = false;

		void update();
		void create_particle(int spawn_x, int spawn_y);
};

#endif