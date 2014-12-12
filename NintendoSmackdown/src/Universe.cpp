#include "Universe.h"

WindowManager* Universe::win_manager;
GameLoop* Universe::game_loop;
Assets* Universe::assets;
Map* Universe::map;
MouseManager* Universe::mouse;
DebugUI* Universe::debug_ui;
InputManager* Universe::input;
EntityManager* Universe::entity_manager;
StateManager* Universe::state;
Editor* Universe::editor;
Camera* Universe::camera;
MapParser* Universe::map_parser;
GameUI* Universe::game_ui;
MenuUI* Universe::menu_ui;
TimerCallback* Universe::timer;
ParticleManager* Universe::particles;
Renderer* Universe::renderer;
OptionsUI* Universe::options_ui;
MessageBoxManager* Universe::messagebox;

void Universe::initiate() {
	srand(time(NULL));

	TTF_Init();

	win_manager = new WindowManager();
	game_loop = new GameLoop();
	assets = new Assets();
	map = new Map();
	mouse = new MouseManager();
	debug_ui = new DebugUI();
	input = new InputManager();
	entity_manager = new EntityManager();
	state = new StateManager();
	editor = new Editor();
	camera = new Camera();
	map_parser = new MapParser();
	game_ui = new GameUI();
	menu_ui = new MenuUI();
	timer = new TimerCallback();
	particles = new ParticleManager();
	renderer = new Renderer();
	options_ui = new OptionsUI();
	messagebox = new MessageBoxManager();

	win_manager->initiate();
	assets->initiate();
	state->initiate();
	input->initiate();
	game_loop->start();
}