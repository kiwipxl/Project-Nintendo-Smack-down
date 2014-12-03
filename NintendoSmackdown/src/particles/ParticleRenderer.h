#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>

class Universe;

class ParticleRenderer {

	public:
		ParticleRenderer();

	private:
		Universe* base_universe;

	protected:
		std::vector<GLfloat> vertices;
		std::vector<GLint> indices;

};

#endif