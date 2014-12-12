#include "Text.h"
#include <sstream>
#include "../../managers/WindowManager.h"
#include "../../managers/Assets.h"
#include "../../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static Renderer* renderer;
};

Text::Text(int x, int y, int size, SDL_Colour font_colour, std::string font_text, 
		   bool smooth, int max_width_align, TextAlign text_align) {
	font_size = size;
	square = TTF_OpenFont("assets/square.ttf", font_size);
	text = font_text;
	colour = font_colour;
	rect.x = x; rect.y = y;
	origin_x = x; origin_y = y;
	font = new Texture();
	rendered = false;
	max_width = max_width_align;
	align = text_align;
	render_text(text, smooth);
}

Text::~Text() {
	TTF_CloseFont(square);
	delete font;
}

void Text::render() {
	universe->renderer->render(font, NULL, &rect);
}

void Text::render_text(std::string font_text, bool smooth) {
	text = font_text;
	SDL_Surface* surface;
	if (smooth) {
		surface = TTF_RenderText_Blended(square, text.c_str(), colour);
	}else {
		surface = TTF_RenderText_Solid(square, text.c_str(), colour);
	}

	font->create_texture(surface);

	TTF_SizeText(square, text.c_str(), &rect.w, &rect.h);
	SDL_FreeSurface(surface);

	update_alignment();

	rendered = true;
}

void Text::update_alignment() {
	rect.x = origin_x; rect.y = origin_y;
	switch (align) {
		case CENTER:
			rect.x = origin_x + (max_width / 2) - (rect.w / 2) - 2;
			break;
		case RIGHT:
			rect.x = origin_x + (max_width - rect.w);
			break;
	}
}