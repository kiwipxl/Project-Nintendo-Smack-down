#include "EntityManager.h"
#include <iostream>

class Universe {

	public:
};

vector<Fighter*> EntityManager::fighters;

EntityManager::EntityManager() {

}

Fighter* EntityManager::createfighter(int x, int y) {
	Fighter* fighter = new Fighter(x, y);
	fighters.push_back(fighter);
	return fighter;
}

void EntityManager::update() {
	for (Fighter* fighter : fighters) {
		fighter->update();
	}
}

void EntityManager::render() {
	for (Fighter* fighter : fighters) {
		fighter->render();
	}
}