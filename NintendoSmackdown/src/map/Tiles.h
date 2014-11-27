#ifndef TILES_H
#define TILES_H

#include <vector>

struct Type {

	Type(int c_sheet_index, int tileindex) : sheet_index(c_sheet_index) { src_x = tileindex * 16; src_y = 0; }

	int sheet_index;
	int src_x;
	int src_y;
};

class Tiles {

	public:
		Tiles() { }

		static Type* NONE;
		static Type* BLOCK;
		static Type* DIRT;

		static std::vector<Type*> types;
		
		static void initiate();
};

#endif