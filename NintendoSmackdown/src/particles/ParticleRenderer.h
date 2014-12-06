#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <SDL.h>
#include <glew.h>
#include <vector>

class Universe;
class Particles;

class ParticleRenderer {

	public:
		ParticleRenderer();

	private:
		Universe* universe;
		Particles* parent;

	protected:
		float timer = 0;

		std::vector<GLfloat> vertices;
		std::vector<GLint> indices;

		void update_renderer();

		void set_renderer_parent(Particles* c_parent) { parent = c_parent; }
};

#endif