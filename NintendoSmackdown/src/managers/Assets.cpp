#include "Assets.h"
#include <iostream>
#include "WindowManager.h"
#include "../tools/ImageTools.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static ImageTools* imagetools;
};

void Assets::initiate() {
	//load sprite sheets
	captainfalconidle = loadtexture("captainfalconidle.png");
}

//loads an image in the assets folder and returns a texture from it
SDL_Texture* Assets::loadtexture(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	SDL_Texture* temp = SDL_CreateTextureFromSurface(universe->winmanager->renderer, surface);
	SDL_FreeSurface(surface);
	textures.push_back(temp);
	return temp;
}

//loads an image in the assets folder and returns a surface from it
SDL_Surface* Assets::loadsurface(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	surfaces.push_back(surface);
	return surface;
}

//free memory from all textures loaded
void Assets::freetextures() {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();
	for (SDL_Surface* surface : surfaces) {
		SDL_FreeSurface(surface);
	}
	surfaces.clear();
}