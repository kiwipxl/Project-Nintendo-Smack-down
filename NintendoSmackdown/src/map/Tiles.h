#ifndef TILES_H
#define TILES_H

struct Type {

	Type(int c_sheetindex, int tileindex) : sheetindex(c_sheetindex) { srcx = tileindex * 16; srcy = 0; }

	int sheetindex;
	int srcx;
	int srcy;
};

class Tiles {

	public:
		Tiles() {

		}

		static Type* NONE;
		static Type* BLOCK;
		static Type* DIRT;
};

#endif