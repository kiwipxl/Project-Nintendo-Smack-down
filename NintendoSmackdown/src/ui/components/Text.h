#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../../tools/Universal.h"
#include "../../renderer/Texture.h"

class Text : Universal {

	public:
		Text(int x, int y, int font_size, SDL_Colour colour, std::string font_text, bool smooth = false);
		~Text();

		SDL_Rect rect;

		void render();
		void render_text(std::string font_text, bool smooth = false);

	private:
		Texture* font;
		bool rendered;
		TTF_Font* square;
		SDL_Colour colour;
		std::string text;
};

#endif