#include "EntityManager.h"
#include <iostream>

class Universe {

	public:
};

EntityManager::EntityManager() {
	playerscreated = 0;
}

Fighter* EntityManager::create_fighter(int x, int y, FighterName fname, FighterType ftype) {
	Fighter* fighter = new Fighter(x, y, fname, ftype);
	fighter->playerid = playerscreated;
	fighter->id = fighters.size();
	fighters.push_back(fighter);
	if (ftype == FighterType::PLAYER) {
		++playerscreated;
	}
	return fighter;
}

void EntityManager::update() {
	for (Fighter* fighter : fighters) {
		fighter->update();
	}
}