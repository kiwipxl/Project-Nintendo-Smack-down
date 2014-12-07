#include "Texture.h"
#include <iostream>

void Texture::create_texture(SDL_Surface* surface) {
	if (surface != NULL) {
		//if the texture is already created then delete the texture but not the buffer
		if (created) {
			glDeleteTextures(1, &id);
			created = false;
		}else {
			//free the buffer if it's already being used and create a new buffer object
			if (buffer_object != NULL) { buffer_object->free(); }
			buffer_object = new BufferObject();
		}

		width = surface->w;
		height = surface->h;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, NULL);
		created = true;
		set_colour(1, 1, 1, 1);
	}
}

void Texture::set_colour(float r, float g, float b, float a) {
	VertexPoint* v = buffer_object->vertex_data;

	for (int n = 0; n < 4; ++n) {
		v[n].colour.r = r;
		v[n].colour.g = g;
		v[n].colour.b = b;
		v[n].colour.a = a;
	}
}

void Texture::free() {
	if (created) {
		glDeleteTextures(1, &id);
		delete buffer_object;
		buffer_object = NULL;
		created = false;
	}
}

Texture::~Texture() {
	free();
}