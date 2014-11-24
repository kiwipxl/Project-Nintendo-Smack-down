#include "Map.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../ui/UIManager.h"
#include "../managers/Assets.h"
#include "Camera.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static Assets* assets;
		static UIManager* uimanager;
		static Camera* camera;
};

Map::Map() {
	created = false;
	gridwidth = universe->winmanager->screenwidth / 32;
	gridheight = universe->winmanager->screenheight / 32;
}

void Map::create() {
	universe->entitymanager->createfighter(250, 500, CAPTAIN_FALCON, PLAYER);
	universe->entitymanager->createfighter(800, 500, CAPTAIN_FALCON, EASYAI);

	created = true;
	for (int x = 0; x < gridwidth; ++x) {
		vector<Node*> row;
		for (int y = 0; y < gridheight; ++y) {
			Node* node = new Node();
			node->type = Tiles::NONE;
			if (x >= 4 && y == 14 && x <= gridwidth - 4) {
				node->type = Tiles::BLOCK; node->solid = true;
			}
			if ((x >= 5 && y == 15 && x <= gridwidth - 5) ||
				(x >= 6 && y == 16 && x <= gridwidth - 6)) {
				node->type = Tiles::DIRT; node->solid = true;
			}
			row.push_back(node);
		}
		nodes.push_back(row);
	}
	srcrect.w = 16; srcrect.h = 16;
	rect.w = 32; rect.h = 32;

	bgsrcrect.x = 0; bgsrcrect.y = 0;
	bgsrcrect.w = 512; bgsrcrect.h = 512;
	bgrect.x = 0; bgrect.y = 0;
	bgrect.w = universe->winmanager->screenwidth; bgrect.h = universe->winmanager->screenheight;
}

void Map::remove() {
	created = false;
}

void Map::update() {
	SDL_RenderCopy(universe->winmanager->renderer, universe->assets->backgroundtiles->t, &bgsrcrect, &bgrect);

	//updates the map
	float scaleoffsetx = universe->camera->getscaleoffsetx(universe->winmanager->screenwidth);
	float scaleoffsety = universe->camera->getscaleoffsety(universe->winmanager->screenheight);
	scaleoffsetx = 0; scaleoffsety = 0;
	float posx = universe->camera->x + scaleoffsetx; float posy = universe->camera->y + scaleoffsety;
	for (int y = 0; y < gridheight; ++y) {
		for (int x = 0; x < gridwidth; ++x) {
			Node* node = nodes[x][y];
			posx += universe->camera->gridsize;
			rect.x = posx; rect.y = posy;
			if (node->type != Tiles::NONE) {
				srcrect.x = node->type->srcx; srcrect.y = node->type->srcy;
				rect.w = ceil(universe->camera->gridsize); rect.h = ceil(universe->camera->gridsize);
				SDL_RenderCopy(universe->winmanager->renderer,
					universe->assets->tilesheets[node->type->sheetindex]->t, &srcrect, &rect);
			}
		}
		posx = 0;
		posy += universe->camera->gridsize;
	}
}