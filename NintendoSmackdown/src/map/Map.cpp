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

}

void Map::initiate() {
	universe->entitymanager->createfighter(0, 0);
}

void Map::update() {

}