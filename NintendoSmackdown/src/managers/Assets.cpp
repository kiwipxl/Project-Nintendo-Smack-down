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
	//load fighter sprite sheets
	fightersheets.push_back(loadtexture("captainfalconidle.png"));
	fightersheets.push_back(loadtexture("captainfalconidle2.png"));
	fightersheets.push_back(loadtexture("captainfalconjump.png"));
	fightersheets.push_back(loadtexture("captainfalconland.png"));
	fightersheets.push_back(loadtexture("captainfalconkicka.png"));
	fightersheets.push_back(loadtexture("captainfalconpuncha.png"));
	fightersheets.push_back(loadtexture("captainfalconroll.png"));
	fightersheets.push_back(loadtexture("captainfalconrunning.png"));
	fightersheets.push_back(loadtexture("captainfalconshield.png"));
	fightersheets.push_back(loadtexture("captainfalconcrouch.png"));
	fightersheets.push_back(loadtexture("captainfalconedgegrab.png"));

	//load tile sprite sheets
	tilesheets.push_back(loadtexture("groundtiles.png"));
}

/**
loads an image in the assets folder and returns a texture from it
**/
Texture* Assets::loadtexture(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	Texture* texture = new Texture(SDL_CreateTextureFromSurface(universe->winmanager->renderer, surface));
	SDL_FreeSurface(surface);
	textures.push_back(texture->t);
	return texture;
}

/**
loads an image in the assets folder and returns a surface from it
**/
SDL_Surface* Assets::loadsurface(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	surfaces.push_back(surface);
	return surface;
}

/**
free memory from all textures loaded
**/
void Assets::freetextures() {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();
	for (SDL_Surface* surface : surfaces) {
		SDL_FreeSurface(surface);
	}
	surfaces.clear();
	tilesheets.clear();
	fightersheets.clear();
}