#ifndef TILES_H
#define TILES_H

struct Type {

	Type(int c_sheetindex, int c_srcx, int c_srcy) : sheetindex(c_sheetindex), srcx(c_srcx), srcy(c_srcy) { }

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
};

#endif