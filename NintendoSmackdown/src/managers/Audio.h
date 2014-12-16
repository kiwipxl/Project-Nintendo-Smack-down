#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "../tools/Universal.h"
#include "../map/Node.h"
#include "../renderer/Texture.h"

class Audio : Universal {

public:
	vector<Texture*> textures;
	vector<Texture*> tile_sheets;
	vector<Texture*> fighter_sheets;

	Texture* background_tiles;
	Texture* menu_boxes_sheet;
	Texture* menu_background;
	Texture* particle_sheet;
	Texture* dropdown_box_sheet;
	Texture* button_sheet;
	Texture* messagebox_sheet;
	Texture* plain_colours;
	Texture* options_background;
	Texture* title_background;

	Texture* selecty;
	Texture* editorUI;
	Texture* editgrid;

	void initiate();

	/**
	loads an image in the assets folder and returns a texture from it
	**/
	Texture* load_texture(char* path, bool dispose_surface = true);

	/**
	free memory from all textures loaded
	**/
	void free_textures();
};

#endif