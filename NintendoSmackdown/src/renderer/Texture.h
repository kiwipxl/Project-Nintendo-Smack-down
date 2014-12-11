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
		BufferObject* buffer_object = NULL;
		SDL_Rect last_src_rect;
		RGBA last_colour;

		void create_texture(SDL_Surface* surface, int buffer_size = 4);
		void set_colour(float r, float g, float b, float a);
		void free();
};

#endif