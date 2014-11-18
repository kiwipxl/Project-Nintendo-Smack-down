#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "../tools/Universal.h"
#include "../map/Node.h"

class Assets : Universal {

	public:
		vector<SDL_Texture*> textures;
		vector<SDL_Surface*> surfaces;
		vector<SDL_Texture*> tilesheets;
		vector<SDL_Texture*> fightersheets;

		void initiate();

		/**
		loads an image in the assets folder and returns a texture from it
		**/
		SDL_Texture* loadtexture(char* path);

		/**
		loads an image in the assets folder and returns a surface from it
		**/
		SDL_Surface* loadsurface(char* path);

		/**
		free memory from all textures loaded
		**/
		void freetextures();
};

#endif