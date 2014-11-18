#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../tools/Universal.h"

enum State {
	TITLESCREEN,	//0
	MAINMENU,		//1
	CHARSELECT,		//2
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
		void switchstate(State newstate);

	private:
		/**
		handles the creation of the new state
		**/
		void createcurrentstate();

		/**
		handles the removing of the current state
		**/
		void removecurrentstate();
};

#endif