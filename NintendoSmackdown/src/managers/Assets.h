#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "../tools/Universal.h"

class Assets : Universal {

	public:
		std::vector<SDL_Texture*> textures;

		void initiate();
		SDL_Texture* loadtexture(char* path);
		void freetextures();
};

#endif