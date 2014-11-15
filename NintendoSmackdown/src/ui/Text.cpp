#include "Text.h"
#include <sstream>
#include "../managers/WindowManager.h"
#include "../managers/Assets.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Assets* assets;
};

Text::Text(int x, int y, int fontsize, SDL_Colour fontcolour, std::string fonttext, bool smooth) {
	square = TTF_OpenFont("assets/square.ttf", fontsize);
	colour = fontcolour;
	rect.x = x; rect.y = y;
	rendered = false;
	rendertext(text, smooth);
}

Text::~Text() {
	TTF_CloseFont(square);
}

void Text::render() {
	SDL_RenderCopy(universe->winmanager->renderer, font, NULL, &rect);
}

void Text::rendertext(std::string fonttext, bool smooth) {
	text = fonttext;
	SDL_Surface* surface;
	if (smooth) {
		surface = TTF_RenderText_Blended(square, text.c_str(), colour);
	}else {
		surface = TTF_RenderText_Solid(square, text.c_str(), colour);
	}

	if (rendered) { SDL_DestroyTexture(font); }
	font = SDL_CreateTextureFromSurface(universe->winmanager->renderer, surface);
	TTF_SizeText(square, text.c_str(), &rect.w, &rect.h);
	SDL_FreeSurface(surface);

	rendered = true;
}