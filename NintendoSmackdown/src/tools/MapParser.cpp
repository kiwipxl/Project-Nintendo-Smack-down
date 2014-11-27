#include "MapParser.h"
#include <iostream>
#include <fstream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Map* map;
};


MapParser::MapParser() {

}

/**
loads data from a file, loads and parses it
**/
void MapParser::load(std::string path) {
	streampos size;
	char* mem_block;

	ifstream file("assets/" + path, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		mem_block = new char[size];
		file.seekg(0, ios::beg);
		file.read(mem_block, size);
		string str_block = mem_block;
		file.close();

		parse(str_block);
	}else {
		cout << "unable to open file " << path.c_str() << "\n";
	}
}

/**
parses and loads from a file
**/
void MapParser::parse(string data) {
	int x = 0;
	int y = 0;
	int size = data.length();

	for (int i = 0; i < size; ++i) {
		if (data[i] == '\r' && data[i + 1] == '\n') {
			x = 0; ++y; ++i;
		}else if (data[i] != ',' && data[i] != ' ') {
			universe->map->nodes[x][y]->type = Tiles::types[data[i] - 48];
			++x;
		}
	}
	cout << "loaded map\n";
}
