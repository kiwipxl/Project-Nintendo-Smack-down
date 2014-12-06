#include "Editor.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../managers/Assets.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
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
}