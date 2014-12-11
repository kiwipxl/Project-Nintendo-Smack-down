#ifndef PARTICLE_H
#define PARTICLE_H

#include "components/ParticleMovement.h"
#include "ParticleTypes.h"
#include "../tools/Point2D.h"

class Particle : public ParticleMovement {

	public:
		Particle(int w, int h, int spawn_x, int spawn_y, ParticleType c_type) 
			: ParticleMovement(spawn_x, spawn_y) {
			width = w;
			height = h;
			type = c_type;
			scale = 1;
			origin.x = width / 2;
			origin.y = height / 2;
			set_movement_parent(this);
			initiate_movement();
		}

		int v_id;
		ParticleType type;
		float scale;
		Point2D origin;
		int width;
		int height;

		void update() {
			update_movement();
		}
};

#endif