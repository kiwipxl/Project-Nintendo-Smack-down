#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>

class Animator {

	public:
		Animator(SDL_Rect* c_srcrect, int c_fps, int c_width, int c_height, int c_srcwidth, int c_srcheight, 
				bool c_loop = true);

		SDL_Rect* srcrect;
		int fps;
		bool loop;

		void update();

	private:
		int fpstimer;
		int width;
		int height;
		int srcwidth;
		int srcheight;
};

#endif