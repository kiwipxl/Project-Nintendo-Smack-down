#include "DebugUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../managers/WindowManager.h"
#include "../GameLoop.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static GameLoop* game_loop;
};

void DebugUI::create() {
	fps_text = new Text(5, 0, 20, { 0, 0, 0 }, "", true);
	std::cout << "debug_ui created\n";
}

void DebugUI::update() {
	fps_text->render();
}

void DebugUI::update_fps_text(int fps) {
	std::string fpsstr = "Fps: ";
	fpsstr += std::to_string(fps);
	fps_text->render_text(fpsstr, true);
}

void DebugUI::remove() {
	delete fps_text;
}