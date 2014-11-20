#include "Universe.h"

WindowManager* Universe::winmanager;
GameLoop* Universe::gameloop;
Assets* Universe::assets;
Map* Universe::map;
MouseManager* Universe::mouse;
UIManager* Universe::uimanager;
KeyboardManager* Universe::keyboard;
EntityManager* Universe::entitymanager;
StateManager* Universe::state;
Editor* Universe::editor;

void Universe::initiate() {
	srand(time(NULL));

	winmanager = new WindowManager();
	gameloop = new GameLoop();
	assets = new Assets();
	map = new Map();
	mouse = new MouseManager();
	uimanager = new UIManager();
	keyboard = new KeyboardManager();
	entitymanager = new EntityManager();
	state = new StateManager();
	editor = new Editor();

	winmanager->initiate();
	assets->initiate();
	uimanager->initiate();
	state->initiate();
	gameloop->start();
}