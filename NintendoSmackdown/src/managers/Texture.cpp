#include "Texture.h"

Texture::Texture(SDL_Texture* c_t) {
	t = c_t;
	SDL_QueryTexture(t, 0, 0, &width, &height);
}