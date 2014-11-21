#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include "../managers/Texture.h"

class Animator {

	public:
		/**
		create the animation class with defined options
		**/
		Animator(Texture* c_t, SDL_Rect* c_srcrect, int c_width, int c_height, int c_fps, 
				bool c_loop = true, bool c_horizontalonly = false);

		SDL_Rect* srcrect;
		bool loop;
		int currentframe;
		bool paused = false;
		Texture* t;
		bool horizontalonly;

		/**
		updates the animator and adds 1 to the fps counter which changes the srcrect position
		**/
		void update();

		/**
		updates the animator with a new texture and width/height
		**/
		void updatetexture(Texture* c_t, int c_width, int c_height, int framesx = -1, int framesy = -1);

		/**
		update fps value
		**/
		void setfps(int newfps);

	private:
		int fps;
		float fpscounter;
		int width;
		int height;
		int srcwidth;
		int srcheight;
};

#endif