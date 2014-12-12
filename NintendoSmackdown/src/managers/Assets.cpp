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
	fighter_sheets.push_back(load_texture("captainfalcon.png", false));

	//load tile sprite sheets
	tile_sheets.push_back(load_texture("groundtiles.png"));

	//load background tile sheets
	background_tiles = load_texture("backgroundtiles.png");

	//load main menu textures and sheets
	menu_boxes_sheet = load_texture("menuboxes.png");
	menu_background = load_texture("menubackground.png");

	//load particle sheet
	particle_sheet = load_texture("particlesheet.png", false);

	//load ui sheets
	dropdown_box_sheet = load_texture("dropdownboxsheet.png");
	button_sheet = load_texture("buttonsheet.png");
	messagebox_sheet = load_texture("messageboxsheet.png");

	//load plain colours
	plain_colours = load_texture("plaincolours.png");
}

/**
loads an image in the assets folder and returns a texture from it
**/
Texture* Assets::load_texture(char* path, bool dispose_surface) {
	std::string texturepath = "assets/";
	texturepath += path;
	SDL_Surface* surface = IMG_Load(texturepath.c_str());
	Texture* texture = new Texture();
	texture->create_texture(surface);
	if (dispose_surface) {
		SDL_FreeSurface(surface);
	}else {
		texture->s = surface;
	}
	textures.push_back(texture);
	return texture;
}

/**
free memory from all textures loaded
**/
void Assets::free_textures() {
	for (Texture* &texture : textures) {
		delete texture;
	}
	textures.clear();
	tile_sheets.clear();
	fighter_sheets.clear();
}