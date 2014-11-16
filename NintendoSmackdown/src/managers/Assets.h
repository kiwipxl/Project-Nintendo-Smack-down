#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "../tools/Universal.h"

class Assets : Universal {

	public:
		vector<SDL_Texture*> textures;
		vector<SDL_Surface*> surfaces;

		//sprite sheets
		SDL_Texture* captainfalconidle;

		void initiate();
		SDL_Texture* loadtexture(char* path);
		SDL_Surface* loadsurface(char* path);
		void freetextures();
};

#endif