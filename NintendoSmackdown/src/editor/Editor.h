#ifndef EDITOR_H
#define EDITOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

class Editor : Universal {

	public:
		Editor();

		void create();
		void update();
		void remove();

	private:
		bool created;
};

#endif