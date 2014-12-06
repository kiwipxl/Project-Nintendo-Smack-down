#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <glew.h>
#include "BufferObject.h"

class Texture {

	public:
		Texture() { created = false; }
		~Texture();
		
		float width;
		float height;
		GLuint id;
		SDL_Surface* s;
		bool created;
		BufferObject* buffer_object;
		SDL_Rect last_src_rect;
		SDL_Rect last_rect;

		void create_texture(SDL_Surface* surface);
};

#endif