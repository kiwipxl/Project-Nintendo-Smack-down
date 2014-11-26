#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Universal.h"
#include "Point2D.h"
#include "../map/Node.h"

class MapParser : Universal {

	public:
		MapParser();

		/**
		loads data from a file, loads and parses it
		**/
		void load(std::string path);

		/**
		parses and loads from a file
		**/
		void parse(std::string data);
};

#endif