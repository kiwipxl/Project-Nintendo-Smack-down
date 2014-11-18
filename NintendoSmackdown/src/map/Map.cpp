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
	gridwidth = 10;
	gridheight = 10;
}

void Map::create() {
	universe->entitymanager->createfighter(0, 0);
	created = true;
	for (int y = 0; y < gridheight; ++y) {
		vector<Node*> row;
		for (int x = 0; x < gridwidth; ++x) {
			Node* node = new Node();
			node->type = Tiles::BLOCK;
			row.push_back(node);
		}
		nodes.push_back(row);
	}
	srcrect.w = 16; srcrect.h = 16;
	rect.w = 64; rect.h = 64;
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
				rect.x = x * 64; rect.y = y * 64;
				SDL_RenderCopy(universe->winmanager->renderer, universe->assets->tilesheets[node->type->sheetindex], &srcrect, &rect);
			}
		}
	}
}