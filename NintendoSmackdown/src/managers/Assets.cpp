#include "Assets.h"
#include <iostream>
#include "WindowManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
};

void Assets::initiate() {

}

SDL_Texture* Assets::loadtexture(char* path) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	SDL_Texture* temp = SDL_CreateTextureFromSurface(universe->winmanager->renderer, surface);
	SDL_FreeSurface(surface);
	textures.push_back(temp);
	return temp;
}

void Assets::freetextures() {
	for (int n = 0; n < textures.size(); ++n) {
		SDL_DestroyTexture(textures.at(n));
	}
	textures.clear();
}