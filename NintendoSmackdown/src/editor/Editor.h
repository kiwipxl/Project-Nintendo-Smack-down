#ifndef EDITOR_H
#define EDITOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"
#include "../map/Node.h"

class Editor : Universal {

public:
	Editor();

	void create();
	void update();
	void remove();
	void changetile();

private:
	bool created;
	int gridwidth;
	int gridheight;

	// Thingos
	bool gridEnabled;
	bool hasClicked;
	int editx;
	int edity;
	int tileIndex;

	// Level size stuff
	int levelSizeX;
	int levelSizeY;
	int offsetX;
	int offsetY;

	vector<vector<Node*>> nodes;
	vector<vector<Node*>> editnode;

	SDL_Rect rect;
	SDL_Rect src_rect;

	//UI rendering
	SDL_Rect uirect;
	SDL_Rect uisrcrect;

	//that button rendering
	SDL_Rect selrect;
	SDL_Rect selsrcrect;

	//AN GRIDS rendering
	SDL_Rect gridrect;
	SDL_Rect gridsrcrect;

	//background rendering
	SDL_Rect bgrect;
	SDL_Rect bgsrc_rect;
};

#endif