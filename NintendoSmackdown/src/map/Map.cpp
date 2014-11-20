#include "Map.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../ui/UIManager.h"
#include "../managers/Assets.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static Assets* assets;
		static UIManager* uimanager;
};

Map::Map() {
	created = false;
	gridwidth = universe->winmanager->screenwidth / 32;
	gridheight = universe->winmanager->screenheight / 32;
}

void Map::create() {
	universe->entitymanager->createfighter(0, 0);
	created = true;
	for (int x = 0; x < gridwidth; ++x) {
		vector<Node*> row;
		for (int y = 0; y < gridheight; ++y) {
			Node* node = new Node();
			node->type = Tiles::NONE;
			if (x >= 4 && y == 14 && x <= gridwidth - 4) { node->type = Tiles::BLOCK; node->solid = true; }
			row.push_back(node);
		}
		nodes.push_back(row);
	}
	srcrect.w = 16; srcrect.h = 16;
	rect.w = 32; rect.h = 32;
}

void Map::remove() {
	created = false;
}

void Map::update() {
	//updates the map
	for (int y = 0; y < gridheight; ++y) {
		for (int x = 0; x < gridwidth; ++x) {
			Node* node = nodes[x][y];
			if (node->type != Tiles::NONE) {
				srcrect.x = node->type->srcx; srcrect.y = node->type->srcy;
				rect.x = x * 32; rect.y = y * 32;
				SDL_RenderCopy(universe->winmanager->renderer, 
					universe->assets->tilesheets[node->type->sheetindex]->t, &srcrect, &rect);
			}
		}
	}
}