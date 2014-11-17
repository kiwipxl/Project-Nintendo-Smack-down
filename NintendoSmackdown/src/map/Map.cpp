#include "Map.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../ui/UIManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static UIManager* uimanager;
};

Map::Map() {
	created = false;
}

void Map::create() {
	universe->entitymanager->createfighter(0, 0);
	created = true;
}

void Map::remove() {
	created = false;
}

void Map::update() {
	//updates the map
}