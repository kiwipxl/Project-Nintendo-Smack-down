#include "Animator.h"
#include <iostream>

/**
Create the animation class with defined options
**/
Animator::Animator(SDL_Texture* c_texture, SDL_Rect* c_srcrect, int c_width, int c_height, 
				   int c_fps, bool c_loop) {
	srcrect = c_srcrect;
	fps = c_fps;
	fpscounter = 0;
	currentframe = 0;
	updatetexture(c_texture, c_width, c_height);
}

/**
Updates the animator and adds 1 to the fps counter which changes the srcrect position
**/
void Animator::update() {
	++fpscounter;
	if (fpscounter >= fps) {
		++currentframe;
		fpscounter = 0;
		srcrect->x += width;
		if (srcrect->x > srcwidth - width) {
			srcrect->x = 0;
			srcrect->y += height;
			if (srcrect->y > srcheight - height) {
				srcrect->y = 0;
			}
		}
	}
}

/**
Updates the animator with a new texture and width/height
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