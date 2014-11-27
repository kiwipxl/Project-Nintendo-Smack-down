#include "EntityManager.h"
#include <iostream>

class Universe {

	public:
};

vector<Fighter*> EntityManager::fighters;

EntityManager::EntityManager() {

}

Fighter* EntityManager::create_fighter(int x, int y, FighterName fname, FighterType ftype) {
	Fighter* fighter = new Fighter(x, y, fname, ftype);
	fighters.push_back(fighter);
	return fighter;
}

void EntityManager::update() {
	for (Fighter* fighter : fighters) {
		fighter->update();
	}
}