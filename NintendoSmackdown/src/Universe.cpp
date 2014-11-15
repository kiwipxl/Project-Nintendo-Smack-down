#include "Universe.h"

WindowManager* Universe::winmanager;
GameLoop* Universe::gameloop;
Assets* Universe::assets;
Map* Universe::map;
ImageTools* Universe::imagetools;
MouseManager* Universe::mouse;
UIManager* Universe::uimanager;
KeyboardManager* Universe::keyboard;
EntityManager* Universe::entitymanager;

void Universe::initiate() {
	srand(time(NULL));

	winmanager = new WindowManager();
	gameloop = new GameLoop();
	assets = new Assets();
	map = new Map();
	imagetools = new ImageTools();
	mouse = new MouseManager();
	uimanager = new UIManager();
	keyboard = new KeyboardManager();
	entitymanager = new EntityManager();

	winmanager->initiate();
	assets->initiate();
	uimanager->initiate();
	map->initiate();
	gameloop->start();
}