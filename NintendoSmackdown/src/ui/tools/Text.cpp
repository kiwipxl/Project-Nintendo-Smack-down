#include "Text.h"
#include <sstream>
#include "../../managers/WindowManager.h"
#include "../../managers/Assets.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
};

Text::Text(int x, int y, int font_size, SDL_Colour font_colour, std::string font_text, bool smooth) {
	square = TTF_OpenFont("assets/square.ttf", font_size);
	text = font_text;
	colour = font_colour;
	rect.x = x; rect.y = y;
	rendered = false;
	render_text(text, smooth);
}

Text::~Text() {
	TTF_CloseFont(square);
}

void Text::render() {
	SDL_RenderCopy(universe->win_manager->renderer, font, NULL, &rect);
}

void Text::render_text(std::string font_text, bool smooth) {
	text = font_text;
	SDL_Surface* surface;
	if (smooth) {
		surface = TTF_RenderText_Blended(square, text.c_str(), colour);
	}else {
		surface = TTF_RenderText_Solid(square, text.c_str(), colour);
	}

	if (rendered) { SDL_DestroyTexture(font); }
	font = SDL_CreateTextureFromSurface(universe->win_manager->renderer, surface);
	TTF_SizeText(square, text.c_str(), &rect.w, &rect.h);
	SDL_FreeSurface(surface);

	rendered = true;
}