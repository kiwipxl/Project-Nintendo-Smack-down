#include "EntityManager.h"
#include <iostream>

class Universe {

	public:
};

EntityManager::EntityManager() {
	players_created = 0;
}

Fighter* EntityManager::create_fighter(int x, int y, FighterName f_name, FighterType f_type) {
	Fighter* fighter = new Fighter(x, y, players_created, fighters.size(), f_name, f_type);
	fighters.push_back(fighter);
	if (f_type == FighterType::PLAYER) {
		++players_created;
	}
	return fighter;
}

void EntityManager::update() {
	for (Fighter* fighter : fighters) {
		fighter->update();
	}
}