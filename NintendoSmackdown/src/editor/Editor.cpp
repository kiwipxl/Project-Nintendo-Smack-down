#include "Editor.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../ui/UIManager.h"
#include "../managers/Assets.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Assets* assets;
		static UIManager* uimanager;
};

Editor::Editor() {
	created = false;
}

void Editor::create() {
	created = true;
}

void Editor::remove() {
	created = false;
}

void Editor::update() {
	//update and render code here
	SDL_RenderCopy(universe->winmanager->renderer, universe->assets->fightersheets[0]->t, NULL, NULL);
}