#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>

class Animator {

	public:
		/**
		Create the animation class with defined options
		**/
		Animator(SDL_Texture* c_texture, SDL_Rect* c_srcrect, int c_width, int c_height, 
				 int c_fps, bool c_loop = true);

		SDL_Rect* srcrect;
		int fps;
		bool loop;
		int currentframe;

		/**
		Updates the animator and adds 1 to the fps counter which changes the srcrect position
		**/
		void update();
		/**
		Updates the animator with a new texture and width/height
		**/
		void updatetexture(SDL_Texture* c_texture, int c_width, int c_height);

	private:
		int fpscounter;
		int width;
		int height;
		int srcwidth;
		int srcheight;
};

#endif