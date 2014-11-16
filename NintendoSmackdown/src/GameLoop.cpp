#include "GameLoop.h"
#include <iostream>
#include <Windows.h>
#include "managers/WindowManager.h"
#include "managers/Assets.h"
#include "map/Map.h"
#include "input/MouseManager.h"
#include "ui/UIManager.h"
#include "input/KeyboardManager.h"
#include "entities/EntityManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Assets* assets;
		static Map* map;
		static MouseManager* mouse;
		static UIManager* uimanager;
		static KeyboardManager* keyboard;
		static EntityManager* entitymanager;
};

void GameLoop::start() {
	msperframe = 1000 / fps;
	startsecondtime = std::clock();

	while (!quit) {
		starttime = std::clock();

		universe->mouse->mousereleased = false;
		while (SDL_PollEvent(&e) != 0) {
			SDL_GetMouseState(&universe->mouse->mousepos.x, &universe->mouse->mousepos.y);

			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			universe->mouse->eventupdate(e);
			universe->keyboard->eventupdate(e);
		}

		universe->map->update();
		universe->uimanager->update();
		universe->entitymanager->update();

		SDL_SetRenderDrawColor(universe->winmanager->renderer, 255, 240, 220, 255);
		SDL_RenderClear(universe->winmanager->renderer);
		universe->entitymanager->render();
		universe->uimanager->render();
		SDL_RenderPresent(universe->winmanager->renderer);

		//SDL_FillRect(universe->winmanager->screensurface, NULL, SDL_MapRGB(universe->winmanager->screensurface->format, 255, 255, 255));
		//SDL_UpdateWindowSurface(universe->winmanager->window);

		double ms = std::clock() - starttime;
		if (ms >= 0 && ms < msperframe) { Sleep(msperframe - ms); }
		++framecounter;
		if (std::clock() - startsecondtime >= 1000) {
			std::cout << "fps: " << framecounter << "\n";
			universe->uimanager->updatefpstext(framecounter);
			framecounter = 0;
			startsecondtime = std::clock();
		}
	}

	universe->assets->freetextures();
	SDL_DestroyWindow(universe->winmanager->window);
	SDL_Quit();
}