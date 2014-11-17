#include "StateManager.h"
#include <iostream>

#include "../editor/Editor.h"
#include "../ui/UIManager.h"
#include "../map/Map.h"
#include "../entities/EntityManager.h"

class Universe {

	public:
		static UIManager* uimanager;
		static Map* map;
		static EntityManager* entitymanager;
		static Editor* editor;
};

/**
Initiates the statemanager and creates the current state
**/
void StateManager::initiate() {
	createcurrentstate();
}

/**
Removes the current state and creates the new state
**/
void StateManager::switchstate(State newstate) {
	removecurrentstate();
	state = newstate;
	createcurrentstate();
}

/**
Handles the creation of the new state
**/
void StateManager::createcurrentstate() {
	switch (state) {
		case TITLESCREEN:
			break;
		case MAINMENU:
			break;
		case CHARSELECT:
			break;
		case GAME:
			universe->map->create();
			break;
		case EDITOR:
			universe->editor->create();
			break;
	}
	std::cout << "created state " << state << "\n";
}

/**
Handles the removing of the current state
**/
void StateManager::removecurrentstate() {
	switch (state) {
		case TITLESCREEN:
			break;
		case MAINMENU:
			break;
		case CHARSELECT:
			break;
		case GAME:
			universe->map->remove();
			break;
		case EDITOR:
			universe->editor->remove();
			break;
	}
	std::cout << "removed state " << state << "\n";
}

/**
Handles updating of everything depending on the state
**/
void StateManager::update() {
	switch (state) {
		case TITLESCREEN:
			break;
		case MAINMENU:
			break;
		case CHARSELECT:
			break;
		case GAME:
			universe->map->update();
			universe->entitymanager->update();
			break;
		case EDITOR:
			universe->uimanager->update();
			universe->editor->update();
			break;
	}
}