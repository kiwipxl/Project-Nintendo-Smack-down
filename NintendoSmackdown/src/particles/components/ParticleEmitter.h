#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

class ParticleController;

class ParticleEmitter {

	public:
		ParticleEmitter(int c_spawn_x, int c_spawn_y, int c_spawn_rate, 
						int c_spawn_amount, int c_max_particles = 1, bool c_spawn_once = true);

		int max_particles;
		int spawn_x;
		int spawn_y;

	private:
		ParticleController* parent;

		int spawn_timer;
		int spawn_rate;
		int spawn_amount;

	protected:
		bool spawned;
		bool spawn_once;

		void update_emitter();
		void set_emitter_parent(ParticleController* c_parent) { parent = c_parent; }
};

#endif