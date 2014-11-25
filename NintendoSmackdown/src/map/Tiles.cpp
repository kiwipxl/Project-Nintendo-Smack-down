#include "Tiles.h"

Type* Tiles::NONE = new Type(0, 0);
Type* Tiles::BLOCK = new Type(0, 1);
Type* Tiles::DIRT = new Type(0, 4);

std::vector<Type*> Tiles::types;

void Tiles::initiate() {
	types.push_back(NONE);
	types.push_back(BLOCK);
	types.push_back(DIRT);
}