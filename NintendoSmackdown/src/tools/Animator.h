#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include "../managers/Texture.h"

class Animator {

	public:
		/**
		create the animation class with defined options
		**/
		Animator(Texture* c_t, SDL_Rect* c_src_rect, int c_width, int c_height, int c_fps, 
				bool c_loop = true, bool c_horizontal_only = false);

		SDL_Rect* src_rect;
		bool loop;
		int current_frame;
		bool paused = false;
		Texture* t;
		bool horizontal_only;

		/**
		updates the animator and adds 1 to the fps counter which changes the srcrect position
		**/
		void update();

		/**
		updates the animator with a new texture and width/height
		**/
		void update_texture(Texture* c_t, int c_width, int c_height, int frames_x = -1, int frames_y = -1);

		/**
		update fps value
		**/
		void set_fps(int new_fps);

	private:
		int fps;
		float fps_counter;
		int width;
		int height;
		int src_width;
		int src_height;
};

#endif