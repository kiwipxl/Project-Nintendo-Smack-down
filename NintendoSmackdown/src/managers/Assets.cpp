#include "Assets.h"
#include <iostream>
#include "WindowManager.h"
#include "../tools/ImageTools.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static ImageTools* imagetools;
};

void Assets::initiate() {
	//load fighter sprite sheets
	fighter_sheets.push_back(load_texture("captainfalcon.png"));

	//load tile sprite sheets
	tile_sheets.push_back(load_texture("groundtiles.png"));

	//load background tile sheets
	background_tiles = load_texture("backgroundtiles.png");
}

/**
loads an image in the assets folder and returns a texture from it
**/
Texture* Assets::load_texture(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	Texture* texture = new Texture(SDL_CreateTextureFromSurface(universe->win_manager->renderer, surface));
	SDL_FreeSurface(surface);
	textures.push_back(texture->t);
	return texture;
}

/**
loads an image in the assets folder and returns a surface from it
**/
SDL_Surface* Assets::load_surface(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	surfaces.push_back(surface);
	return surface;
}

/**
free memory from all textures loaded
**/
void Assets::free_textures() {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();
	for (SDL_Surface* surface : surfaces) {
		SDL_FreeSurface(surface);
	}
	surfaces.clear();
	tile_sheets.clear();
	fighter_sheets.clear();
}