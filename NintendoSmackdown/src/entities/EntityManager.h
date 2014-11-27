#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include "../tools/Universal.h"
#include "fighters/Fighter.h"

class EntityManager : Universal {

	public:
		EntityManager();
		
		vector<Fighter*> fighters;
		int playerscreated;
		
		Fighter* create_fighter(int x, int y, FighterName fname, FighterType ftype);

		void update();
};

#endif