#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../../tools/Universal.h"
#include "../../renderer/Texture.h"

enum TextAlign {
	LEFT,
	CENTER,
	RIGHT
};

class Text : Universal {

	public:
		Text(int x, int y, int size, SDL_Colour colour, std::string font_text,
			bool smooth = false, int max_width_align = 0, TextAlign text_align = LEFT);
		~Text();

		SDL_Rect rect;
		int origin_x;
		int origin_y;
		int max_width;

		void render();
		void render_text(std::string font_text, bool smooth = false);

		std::string get_text() { return text; }
		int get_font_size() { return font_size; }

		void update_alignment();

	private:
		Texture* font;
		bool rendered;
		TTF_Font* square;
		SDL_Colour colour;
		std::string text;
		TextAlign align;
		int font_size;
};

#endif