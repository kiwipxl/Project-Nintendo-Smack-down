#include "GameLoop.h"
#include <iostream>
#include <Windows.h>
#include "managers/WindowManager.h"
#include "managers/Assets.h"
#include "input/MouseManager.h"
#include "ui/DebugUI.h"
#include "input/InputManager.h"
#include "managers/StateManager.h"
#include "map/Camera.h"
#include "tools/timer/TimerCallback.h"
#include "renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static MouseManager* mouse;
		static DebugUI* debug_ui;
		static InputManager* input;
		static StateManager* state;
		static TimerCallback* timer;
		static Renderer* renderer;
};

void GameLoop::start() {
	ms_per_frame = 1000 / fps;
	start_second_time = std::clock();

	SDL_JoystickEventState(SDL_ENABLE);

	while (!quit) {
		start_time = std::clock();

		universe->mouse->mouse_released = false;
		while (SDL_PollEvent(&e) != 0) {
			SDL_GetMouseState(&universe->mouse->mouse_pos.x, &universe->mouse->mouse_pos.y);

			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}else if (e.type == SDL_WINDOWEVENT) {
				universe->win_manager->update_resize();
			}
			universe->mouse->event_update(e);
			universe->input->event_update(e);
		}

		//reset render call variables
		universe->renderer->render_calls = 0;
		universe->renderer->transform_render_calls = 0;
		universe->renderer->vertices_uploaded = 0;
		universe->renderer->total_render_calls = 0;

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		std::clock_t start_render = std::clock();
		universe->timer->update();
		universe->state->update();

		//update render info
		universe->debug_ui->update_render_info();

		//swaps back buffer to front buffer
		SDL_GL_SwapWindow(universe->win_manager->window);

		/**
		SDL_SetRenderDrawColor(universe->win_manager->renderer, 255, 240, 220, 255);
		SDL_RenderClear(universe->win_manager->renderer);
		universe->timer->update();
		universe->state->update();
		SDL_RenderPresent(universe->win_manager->renderer);
		**/

		//SDL_FillRect(universe->win_manager->screensurface, NULL, SDL_MapRGB(universe->win_manager->screensurface->format, 255, 255, 255));
		//SDL_UpdateWindowSurface(universe->win_manager->window);

		double ms = std::clock() - start_time;
		if (ms >= 0 && ms < ms_per_frame - 1) { Sleep(floor(ms_per_frame - ms - 1)); }

		++frame_counter;
		if (std::clock() - start_second_time >= 1000) {
			std::cout << "fps: " << frame_counter << "\n";
			universe->debug_ui->update_fps_text(frame_counter);
			frame_counter = 0;
			start_second_time = std::clock();
		}
	}

	universe->assets->free_textures();
	SDL_DestroyWindow(universe->win_manager->window);
	SDL_Quit();
}