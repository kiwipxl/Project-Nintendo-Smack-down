#ifndef TILES_H
#define TILES_H

#include <vector>

struct Type {

	Type(int c_sheetindex, int tileindex) : sheetindex(c_sheetindex) { srcx = tileindex * 16; srcy = 0; }

	int sheetindex;
	int srcx;
	int srcy;
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