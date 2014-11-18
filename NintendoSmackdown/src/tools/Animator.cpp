#include "Animator.h"
#include <iostream>

/**
create the animation class with defined options
**/
Animator::Animator(SDL_Texture* c_texture, SDL_Rect* c_srcrect, int c_width, int c_height, 
				   int c_fps, bool c_loop) {
	srcrect = c_srcrect;
	fpscounter = 0;
	currentframe = 0;
	loop = c_loop;
	setfps(c_fps);
	updatetexture(c_texture, c_width, c_height);
}

/**
updates the animator and adds 1 to the fps counter which changes the srcrect position
**/
void Animator::update() {
	if (!paused) {
		++fpscounter;
		if (fpscounter >= fps) {
			++currentframe;
			fpscounter = 0;
			srcrect->x += width;
			if (srcrect->x > srcwidth - width) {
				srcrect->y += height;
				if (srcrect->y > srcheight - height) {
					if (!loop) { srcrect->x -= width; srcrect->y -= height; paused = true; return; }
					srcrect->y = 0;
				}
				srcrect->x = 0;
			}
		}
	}
}

/**
updates the animator with a new texture and width/height
**/
void Animator::updatetexture(SDL_Texture* c_texture, int c_width, int c_height) {
	fpscounter = 0;
	currentframe = 0;
	width = c_width;
	height = c_height;
	srcrect->w = width;
	srcrect->h = height;
	SDL_QueryTexture(c_texture, 0, 0, &srcwidth, &srcheight);
}

/**
update fps value
**/
void Animator::setfps(int newfps) {
	fps = 60 / newfps;
}