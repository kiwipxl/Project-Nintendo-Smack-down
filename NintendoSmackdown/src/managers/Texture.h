#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

class Texture {

	public:
		Texture() { }
		Texture(SDL_Texture* c_t);

		SDL_Texture* t;
		SDL_Surface* s;
		int width;
		int height;
};

#endif