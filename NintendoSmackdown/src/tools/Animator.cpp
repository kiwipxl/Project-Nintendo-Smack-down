#include "Animator.h"
#include <iostream>

/**
create the animation class with defined options
**/
Animator::Animator(Texture* c_t, SDL_Rect* c_srcrect, int c_width, int c_height, int c_fps, 
				   bool c_loop, bool c_horizontalonly) {
	srcrect = c_srcrect;
	fpscounter = 0;
	currentframe = 0;
	loop = c_loop;
	horizontalonly = c_horizontalonly;
	setfps(c_fps);
	updatetexture(c_t, c_width, c_height);
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
				if (!horizontalonly) {
					srcrect->y += height;
					if (srcrect->y > srcheight - height) {
						if (!loop) { srcrect->x -= width; srcrect->y -= height; paused = true; return; }
						srcrect->y = 0;
					}
				}else if (!loop) { srcrect->x -= width; paused = true; return; }
				srcrect->x = 0;
			}
		}
	}
}

/**
updates the animator with a new texture and width/height
**/
void Animator::updatetexture(Texture* c_t, int c_width, int c_height, int framesx, int framesy) {
	fpscounter = 0;
	currentframe = 0;
	width = c_width;
	height = c_height;
	t = c_t;
	srcwidth = t->width;
	srcheight = t->height;
	srcrect->x = 0;
	srcrect->y = 0;
	srcrect->w = width;
	srcrect->h = height;
	if (framesx != -1) { srcwidth = framesx * width; } if (framesy != -1) { srcheight = framesy * height; }
}

/**
update fps value
**/
void Animator::setfps(int newfps) {
	fps = 60 / newfps;
}