#include "Texture.h"
#include <iostream>

void Texture::create_texture(SDL_Surface* surface) {
	if (surface != NULL) {
		width = surface->w;	
		height = surface->h;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, NULL);
		buffer_object = new BufferObject();
		created = true;
	}
}

Texture::~Texture() {
	//todo delete texture from gpu memory
}