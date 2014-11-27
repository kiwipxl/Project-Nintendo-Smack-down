#ifndef ASSETS_H
#define ASSETS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "../tools/Universal.h"
#include "../map/Node.h"
#include "Texture.h"

class Assets : Universal {

	public:
		vector<SDL_Texture*> textures;
		vector<SDL_Surface*> surfaces;
		vector<Texture*> tile_sheets;
		vector<Texture*> fighter_sheets;

		Texture* background_tiles;

		void initiate();

		/**
		loads an image in the assets folder and returns a texture from it
		**/
		Texture* load_texture(char* path);

		/**
		loads an image in the assets folder and returns a surface from it
		**/
		SDL_Surface* load_surface(char* path);

		/**
		free memory from all textures loaded
		**/
		void free_textures();
};

#endif