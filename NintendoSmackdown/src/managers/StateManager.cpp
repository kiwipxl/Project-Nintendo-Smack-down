#include "StateManager.h"
#include <iostream>

#include "../editor/Editor.h"
#include "../ui/DebugUI.h"
#include "../map/Map.h"
#include "../entities/EntityManager.h"
#include "../map/Camera.h"
#include "../ui/GameUI.h"
#include "../ui/MenuUI.h"
#include "../input/InputManager.h"
#include "WindowManager.h"
#include "../particles/ParticleManager.h"
#include "../ui/OptionsUI.h"
#include "../ui/MessageBoxManager.h"
#include "../ui/TitleUI.h"
#include "Audio.h"
#include "../ui/FighterSelectUI.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static DebugUI* debug_ui;
		static Map* map;
		static EntityManager* entity_manager;
		static Editor* editor;
		static Camera* camera;
		static GameUI* game_ui;
		static MenuUI* menu_ui;
		static InputManager* input;
		static ParticleManager* particles;
		static OptionsUI* options_ui;
		static MessageBoxManager* messagebox;
		static TitleUI* title_ui;
		static Audio* audio;
		static FighterSelectUI* fighter_select_ui;
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
	universe->debug_ui->create();
	switch (state) {
		case TITLE_SCREEN:
			universe->title_ui->create();
			universe->audio->play_music(universe->audio->pirate_song, INT_MAX);
			break;
		case MAIN_MENU:
			universe->menu_ui->create();
			universe->audio->play_music(universe->audio->pirate_song, INT_MAX);
			break;
		case OPTIONS:
			universe->options_ui->create();
			universe->audio->play_music(universe->audio->pirate_song, INT_MAX);
			break;
		case CHAR_SELECT:
			universe->fighter_select_ui->create();
			universe->audio->play_music(universe->audio->pirate_song, INT_MAX);
			break;
		case GAME:
			universe->camera->reset();
			universe->map->create();
			universe->game_ui->create();
			universe->audio->play_music(universe->audio->theme_song, 0);
			break;
		case EDITOR:
			universe->editor->create();
			universe->audio->play_music(universe->audio->pirate_song, INT_MAX);
			break;
	}
	std::cout << "created state " << state << "\n";
}

/**
handles the removing of the current state
**/
void StateManager::remove_current_state() {
	universe->debug_ui->remove();
	universe->messagebox->hide();
	switch (state) {
		case TITLE_SCREEN:
			universe->title_ui->remove();
			break;
		case MAIN_MENU:
			universe->menu_ui->remove();
			break;
		case OPTIONS:
			universe->options_ui->remove();
			break;
		case CHAR_SELECT:
			universe->fighter_select_ui->remove();
			break;
		case GAME:
			universe->map->remove();
			universe->game_ui->remove();
			break;
		case EDITOR:
			universe->editor->remove();
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
			universe->title_ui->update();
			break;
		case MAIN_MENU:
			universe->menu_ui->update();
			break;
		case OPTIONS:
			universe->options_ui->update();
			break;
		case CHAR_SELECT:
			universe->fighter_select_ui->update();
			break;
		case GAME:
			universe->camera->update();
			universe->map->update();
			universe->entity_manager->update();
			universe->particles->update();
			universe->game_ui->update();
			universe->debug_ui->update();
			break;
		case EDITOR:
			universe->editor->update();
			break;
	}
	universe->audio->update();
	universe->input->update();
	universe->messagebox->update();
}

/**
calls a resize function for parts in the state
**/
void StateManager::resize_current_state() {
	int w = universe->win_manager->screen_width;
	int h = universe->win_manager->screen_height;
	switch (state) {
		case TITLE_SCREEN:
			break;
		case MAIN_MENU:
			universe->menu_ui->resize_update(w, h);
			break;
		case OPTIONS:
			universe->options_ui->resize_update(w, h);
			break;
		case CHAR_SELECT:
			universe->fighter_select_ui->resize_update(w, h);
			break;
		case GAME:
			universe->map->resize_update(w, h);
			universe->game_ui->resize_update(w, h);
			break;
		case EDITOR:
			break;
	}
	universe->messagebox->resize_update(w, h);
}