#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <vector>
#include "../../renderer/Texture.h"

class Universe;
class ParticleController;

class ParticleRenderer {

	public:
		ParticleRenderer() { }

	private:
		Universe* universe;
		ParticleController* parent;
		GLfloat* matrices;

		SDL_Rect src_rect;

	protected:
		Texture* texture;

		void create_texture();
		void update_renderer();

		void set_renderer_parent(ParticleController* c_parent) { parent = c_parent; }
};

#endif