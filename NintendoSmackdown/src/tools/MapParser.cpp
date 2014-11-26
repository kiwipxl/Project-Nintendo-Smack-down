#include "MapParser.h"
#include <iostream>
#include <fstream>
#include "../managers/WindowManager.h"
#include "../entities/EntityManager.h"
#include "../ui/UIManager.h"
#include "../managers/Assets.h"
#include "../map/Map.h"
#include "../map/Tiles.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static EntityManager* entitymanager;
		static Assets* assets;
		static UIManager* uimanager;
		static MapParser* mapParser;
		static Map* map;
};


MapParser::MapParser() {

}

/**
loads data from a file, loads and parses it
**/
void MapParser::load(std::string path) {
	streampos size;
	char* memblock;

	ifstream file("assets/" + path, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		string strblock = memblock;
		file.close();

		parse(strblock);
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
