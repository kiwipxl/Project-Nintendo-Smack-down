#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../tools/Universal.h"

enum State {
	TITLE_SCREEN,	//0
	MAIN_MENU,		//1
	CHAR_SELECT,		//2
	GAME,			//3
	EDITOR			//4
};

class StateManager : Universal {

	public:
		StateManager() {
			state = GAME;
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