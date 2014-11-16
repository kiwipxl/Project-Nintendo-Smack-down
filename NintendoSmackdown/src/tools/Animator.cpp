#include "Animator.h"
#include <iostream>

Animator::Animator(SDL_Rect* c_srcrect, int c_fps, int c_width, int c_height, int c_srcwidth, int c_srcheight, bool c_loop) {
	srcrect = c_srcrect;
	fps = c_fps;
	width = c_width;
	height = c_height;
	srcwidth = c_srcwidth;
	srcheight = c_srcheight;
	fpstimer = 0;
}

/**
Updates the animator
**/
void Animator::update() {
	++fpstimer;
	if (fpstimer >= fps) {
		fpstimer = 0;
		srcrect->x += width;
		if (srcrect->x >= srcwidth) {
			srcrect->x = 0;
		}
	}
}