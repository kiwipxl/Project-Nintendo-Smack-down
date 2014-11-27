#include "Map.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../managers/Assets.h"
#include "Camera.h"
#include "../tools/MapParser.h"
#include "../ui/GameUI.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static EntityManager* entity_manager;
		static Assets* assets;
		static Camera* camera;
		static MapParser* map_parser;
		static GameUI* game_ui;
};

Map::Map() {
	created = false;
	grid_width = universe->win_manager->screen_width / 32;
	grid_height = universe->win_manager->screen_height / 32;
}

void Map::create() {
	Tiles::initiate();

	universe->entity_manager->create_fighter(250, 250, CAPTAIN_FALCON, PLAYER);
	universe->entity_manager->create_fighter(500, 250, CAPTAIN_FALCON, EASYAI);

	universe->game_ui->create_damage_texts(2);

	created = true;
	for (int x = 0; x < grid_width; ++x) {
		vector<Node*> row;
		for (int y = 0; y < grid_height; ++y) {
			Node* node = new Node();
			node->type = Tiles::NONE;
			if (x >= 4 && y == 14 && x <= grid_width - 4) {
				node->type = Tiles::BLOCK; node->solid = true;
			}
			if ((x >= 5 && y == 15 && x <= grid_width - 5) ||
				(x >= 6 && y == 16 && x <= grid_width - 6)) {
				node->type = Tiles::DIRT; node->solid = true;
			}
			row.push_back(node);
		}
		nodes.push_back(row);
	}
	src_rect.w = 16; src_rect.h = 16;
	rect.w = 32; rect.h = 32;

	bgsrc_rect.x = 512; bgsrc_rect.y = 0;
	bgsrc_rect.w = 512; bgsrc_rect.h = 432;
	bgrect.x = 0; bgrect.y = 0;
	bgrect.w = universe->win_manager->screen_width; bgrect.h = universe->win_manager->screen_height;

	//nodes[12][13]->type = Tiles::BLOCK;
	//nodes[12][13]->solid = true;

	universe->map_parser->load("map1.txt");

	map_width = grid_width * (32 * universe->camera->scale);
	map_height = grid_height * (32 * universe->camera->scale);
}

void Map::remove() {
	created = false;
}

void Map::update() {
	map_width = grid_width * (32 * universe->camera->scale);
	map_height = grid_height * (32 * universe->camera->scale);

	float pos_x = universe->camera->x + universe->camera->get_offset_x(0);
	float pos_y = universe->camera->y + universe->camera->get_offset_y(0);
	bgrect.x = -abs(universe->camera->x + pos_x) / 10; bgrect.y = -abs(universe->camera->y + pos_y) / 10;
	bgrect.w = universe->win_manager->screen_width - bgrect.x;
	bgrect.h = bgrect.w;
	SDL_RenderCopy(universe->win_manager->renderer, universe->assets->background_tiles->t, &bgsrc_rect, &bgrect);

	//updates the map
	pos_x = universe->camera->x + universe->camera->get_offset_x(0);
	pos_y = universe->camera->y + universe->camera->get_offset_y(0);
	for (int y = 0; y < grid_height; ++y) {
		for (int x = 0; x < grid_width; ++x) {
			Node* node = nodes[x][y];
			rect.x = pos_x; rect.y = pos_y;
			if (node->type != Tiles::NONE) {
				src_rect.x = node->type->src_x; src_rect.y = node->type->src_y;
				rect.w = ceil(universe->camera->grid_size); rect.h = ceil(universe->camera->grid_size);
				SDL_RenderCopy(universe->win_manager->renderer,
					universe->assets->tile_sheets[node->type->sheet_index]->t, &src_rect, &rect);
			}
			pos_x += universe->camera->grid_size;
		}
		pos_x = universe->camera->x + universe->camera->get_offset_x(0);
		pos_y += universe->camera->grid_size;
	}
}