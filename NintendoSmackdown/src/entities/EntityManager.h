#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include "../tools/Universal.h"
#include "Item.h"

class EntityManager : Universal {

	public:
		EntityManager();

		//static vector<Item*> items;

		//static Item* createitem(int x, int y);

		void update();
		void render();
};

#endif