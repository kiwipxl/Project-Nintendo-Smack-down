#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <glew.h>
#include <vector>
#include "Texture.h"

class Universe;

class Renderer {

	public:
		Renderer();

		int render_calls = 0;
		int transform_render_calls = 0;
		int vertices_uploaded = 0;
		int total_render_calls = 0;

		void render(Texture* texture, SDL_Rect* src_rect, SDL_Rect* rect);
		void render_transform(Texture* texture, SDL_Rect* src_rect, SDL_Rect* rect, 
							  float angle, SDL_Point* origin, SDL_RendererFlip flip);

	private:
		Universe* universe;
		
		bool set_buffer(Texture* texture, SDL_Rect* src_rect);
		void draw_buffer(Texture* texture, bool upload_buffer = false);
};

#endif