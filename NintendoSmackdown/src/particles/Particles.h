#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleEmitter.h"
#include "ParticleRenderer.h"

class Particles : ParticleRenderer, ParticleEmitter {

	public:
		Particles(ParticleEmitter* emitter);

		void update();
};

#endif