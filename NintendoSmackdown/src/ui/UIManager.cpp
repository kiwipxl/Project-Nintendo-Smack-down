#include "UIManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../managers/WindowManager.h"
#include "../GameLoop.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static GameLoop* gameloop;
};

void UIManager::initiate() {
	TTF_Init();
	fpstext = new Text(5, 0, 20, { 0, 0, 0 }, "", true);
	std::cout << "uimanager initiated\n";
}

void UIManager::update() {
	fpstext->render();
}

void UIManager::updatefpstext(int fps) {
	std::string fpsstr = "Fps: ";
	fpsstr += std::to_string(fps);
	fpstext->rendertext(fpsstr, true);
}

void UIManager::remove() {
	delete fpstext;
}