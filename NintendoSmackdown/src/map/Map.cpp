#include "Map.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../ui/UIManager.h"
#include "../managers/Assets.h"
#include "Camera.h"
#include "../tools/MapParser.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static Assets* assets;
		static UIManager* uimanager;
		static Camera* camera;
		static MapParser* mapparser;
};

Map::Map() {
	created = false;
	gridwidth = universe->winmanager->screenwidth / 32;
	gridheight = universe->winmanager->screenheight / 32;
}

void Map::create() {
	Tiles::initiate();

	universe->entitymanager->createfighter(250, 250, CAPTAIN_FALCON, PLAYER);
	universe->entitymanager->createfighter(500, 250, CAPTAIN_FALCON, EASYAI);

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

	bgsrcrect.x = 512; bgsrcrect.y = 0;
	bgsrcrect.w = 512; bgsrcrect.h = 432;
	bgrect.x = 0; bgrect.y = 0;
	bgrect.w = universe->winmanager->screenwidth; bgrect.h = universe->winmanager->screenheight;

	//nodes[12][13]->type = Tiles::BLOCK;
	//nodes[12][13]->solid = true;

	universe->mapparser->load("map1.txt");

	mapwidth = gridwidth * (32 * universe->camera->scale);
	mapheight = gridheight * (32 * universe->camera->scale);
}

void Map::remove() {
	created = false;
}

void Map::update() {
	mapwidth = gridwidth * (32 * universe->camera->scale);
	mapheight = gridheight * (32 * universe->camera->scale);

	float posx = universe->camera->x + universe->camera->getoffsetx(0);
	float posy = universe->camera->y + universe->camera->getoffsety(0);
	bgrect.x = -abs(universe->camera->x + posx) / 10; bgrect.y = -abs(universe->camera->y + posy) / 10;
	bgrect.w = universe->winmanager->screenwidth - bgrect.x;
	bgrect.h = bgrect.w;
	SDL_RenderCopy(universe->winmanager->renderer, universe->assets->backgroundtiles->t, &bgsrcrect, &bgrect);

	//updates the map
	posx = universe->camera->x + universe->camera->getoffsetx(0);
	posy = universe->camera->y + universe->camera->getoffsety(0);
	for (int y = 0; y < gridheight; ++y) {
		for (int x = 0; x < gridwidth; ++x) {
			Node* node = nodes[x][y];
			rect.x = posx; rect.y = posy;
			if (node->type != Tiles::NONE) {
				srcrect.x = node->type->srcx; srcrect.y = node->type->srcy;
				rect.w = ceil(universe->camera->gridsize); rect.h = ceil(universe->camera->gridsize);
				SDL_RenderCopy(universe->winmanager->renderer,
					universe->assets->tilesheets[node->type->sheetindex]->t, &srcrect, &rect);
			}
			posx += universe->camera->gridsize;
		}
		posx = universe->camera->x + universe->camera->getoffsetx(0);
		posy += universe->camera->gridsize;
	}
}