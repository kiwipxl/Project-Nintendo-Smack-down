#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../tools/Universal.h"
#include "Fighter.h"

class EntityManager : Universal {

	public:
		EntityManager();

		static vector<Fighter*> fighters;

		static Fighter* createfighter(int x, int y);

		void update();
};

#endif