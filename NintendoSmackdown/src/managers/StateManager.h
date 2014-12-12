#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../tools/Universal.h"

enum State {
	TITLE_SCREEN,	//0
	MAIN_MENU,		//1
	OPTIONS,		//2
	CHAR_SELECT,	//3
	GAME,			//4
	EDITOR			//5
};

class StateManager : Universal {

	public:
		StateManager() {
			state = MAIN_MENU;
		}

		State state;

		/**
		initiates the statemanager and creates the current state
		**/
		void initiate();

		/**
		handles updating of everything depending on the state
		**/
		void update();

		/**
		removes the current state and creates the new state
		**/
		void switch_state(State new_state);

		/**
		calls a resize function for parts in the state
		**/
		void resize_current_state();

	private:
		/**
		handles the creation of the new state
		**/
		void create_current_state();

		/**
		handles the removing of the current state
		**/
		void remove_current_state();
};

#endif