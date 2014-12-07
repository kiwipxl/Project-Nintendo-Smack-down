#include "Animator.h"
#include <iostream>

/**
create the animation class with defined options
**/
Animator::Animator(Texture* c_t, SDL_Rect* c_src_rect, int c_width, int c_height, int c_fps, 
				   bool c_loop, bool c_horizontal_only) {
	src_rect = c_src_rect;
	fps_counter = 0;
	current_frame = 0;
	loop = c_loop;
	horizontal_only = c_horizontal_only;
	set_fps(c_fps);
	update_texture(c_t, c_width, c_height);
}

/**
updates the animator and adds 1 to the fps counter which changes the srcrect position
**/
void Animator::update() {
	if (!paused) {
		++fps_counter;
		if (fps_counter >= fps) {
			next_frame();
		}
	}
}

/**
plays the next frame
**/
void Animator::next_frame() {
	++current_frame;
	fps_counter = 0;
	src_rect->x += width;
	if (src_rect->x > src_width - width) {
		if (!horizontal_only) {
			src_rect->y += height;
			if (src_rect->y > src_height - height) {
				if (!loop) { src_rect->x -= width; src_rect->y -= height; paused = true; return; }
				src_rect->y = 0;
				current_frame = 0;
			}
		}else if (!loop) { src_rect->x -= width; paused = true; return; }
		src_rect->x = 0;
		if (horizontal_only) { current_frame = 0; }
	}
}

/**
updates the animator with a new texture and width/height
**/
void Animator::update_texture(Texture* c_t, int c_width, int c_height, int frames_x, int frames_y) {
	fps_counter = 0;
	current_frame = 0;
	width = c_width;
	height = c_height;
	t = c_t;
	src_width = t->width;
	src_height = t->height;
	src_rect->x = 0;
	src_rect->y = 0;
	src_rect->w = width;
	src_rect->h = height;
	if (frames_x != -1) { src_width = frames_x * width; } if (frames_y != -1) { src_height = frames_y * height; }
}

/**
update fps value
**/
void Animator::set_fps(int new_fps) {
	fps = 60 / new_fps;
}