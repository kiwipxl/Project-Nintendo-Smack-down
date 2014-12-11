#ifndef PARTICLE_MOVEMENT_H
#define PARTICLE_MOVEMENT_H

#include "../../tools/Point2DF.h"
#include "../../tools/Universal.h"
#include <vector>

class Particle;

class ParticleMovement : Universal {

	public:
		ParticleMovement(int c_spawn_x, int c_spawn_y);

		Point2DF pos;
		Point2DF accel;
		bool removed = false;
		float rotation;
		int spawn_x;
		int spawn_y;

	private:
		Particle* parent;

		float speedx;
		float gravity;

		int remove_timer = 0;
		int remove_rate = 100;

	protected:
		void initiate_movement();
		void update_movement();
		void set_movement_parent(Particle* c_parent) { parent = c_parent; }
};

#endif