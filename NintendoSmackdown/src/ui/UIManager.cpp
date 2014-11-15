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
	SDL_Color colour;
	fpstext = new Text(0, 0, 2, { 0, 0, 0 }, "", true);
	std::cout << "uimanager initiated\n";
}

void UIManager::update() {

}

void UIManager::render() {
	fpstext->render();
}

void UIManager::updatefpstext(int fps) {
	std::string fpsstr = "Fps: ";
	fpsstr += std::to_string((long double)fps);
	fpstext->rendertext(fpsstr, true);
}