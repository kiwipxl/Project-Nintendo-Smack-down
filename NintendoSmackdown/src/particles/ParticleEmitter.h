#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <iostream>

class Particles;

class ParticleEmitter {

	public:
		ParticleEmitter(int c_spawn_x, int c_spawn_y, int c_spawn_rate, 
						int c_spawn_amount, bool c_spawn_once = true);

	private:
		Particles* parent;

		int spawn_timer;
		bool spawned;

	protected:
		int spawn_x;
		int spawn_y;
		int spawn_rate;
		int spawn_amount;
		bool spawn_once;

		void update_emitter();
		void set_emitter_parent(Particles* c_parent) { parent = c_parent; }
};

#endif