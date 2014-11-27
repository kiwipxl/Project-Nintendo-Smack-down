#include "StateManager.h"
#include <iostream>

#include "../editor/Editor.h"
#include "../ui/DebugUI.h"
#include "../map/Map.h"
#include "../entities/EntityManager.h"
#include "../map/Camera.h"
#include "../ui/GameUI.h"

class Universe {

	public:
		static DebugUI* debug_ui;
		static Map* map;
		static EntityManager* entity_manager;
		static Editor* editor;
		static Camera* camera;
		static GameUI* game_ui;
};

/**
initiates the statemanager and creates the current state
**/
void StateManager::initiate() {
	create_current_state();
}

/**
removes the current state and creates the new state
**/
void StateManager::switch_state(State new_state) {
	remove_current_state();
	state = new_state;
	create_current_state();
}

/**
handles the creation of the new state
**/
void StateManager::create_current_state() {
	switch (state) {
		case TITLE_SCREEN:
			break;
		case MAIN_MENU:
			break;
		case CHAR_SELECT:
			break;
		case GAME:
			universe->camera->reset();
			universe->map->create();
			universe->debug_ui->create();
			universe->game_ui->create();
			break;
		case EDITOR:
			universe->editor->create();
			universe->debug_ui->create();
			break;
	}
	std::cout << "created state " << state << "\n";
}

/**
handles the removing of the current state
**/
void StateManager::remove_current_state() {
	switch (state) {
		case TITLE_SCREEN:
			break;
		case MAIN_MENU:
			break;
		case CHAR_SELECT:
			break;
		case GAME:
			universe->map->remove();
			universe->debug_ui->remove();
			universe->game_ui->remove();
			break;
		case EDITOR:
			universe->editor->remove();
			universe->debug_ui->remove();
			break;
	}
	std::cout << "removed state " << state << "\n";
}

/**
handles updating of everything depending on the state
**/
void StateManager::update() {
	switch (state) {
		case TITLE_SCREEN:
			break;
		case MAIN_MENU:
			break;
		case CHAR_SELECT:
			break;
		case GAME:
			universe->camera->update();
			universe->map->update();
			universe->entity_manager->update();
			universe->debug_ui->update();
			universe->game_ui->update();
			break;
		case EDITOR:
			universe->debug_ui->update();
			universe->editor->update();
			universe->debug_ui->update();
			break;
	}
}