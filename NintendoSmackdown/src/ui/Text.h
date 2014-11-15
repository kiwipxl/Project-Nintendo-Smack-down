#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../tools/Universal.h"

class Text : Universal {

	public:
		Text(int x, int y, int fontsize, SDL_Colour colour, std::string fonttext, bool smooth = false);
		~Text();

		void render();
		void rendertext(std::string fonttext, bool smooth = false);

	private:
		SDL_Texture* font;
		bool rendered;
		SDL_Rect rect;
		TTF_Font* square;
		SDL_Colour colour;
		std::string text;
};

#endif