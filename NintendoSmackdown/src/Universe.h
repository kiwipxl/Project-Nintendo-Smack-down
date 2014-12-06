#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "managers/WindowManager.h"
#include "managers/Assets.h"
#include "GameLoop.h"
#include "map/Map.h"
#include "tools/Point2D.h"
#include "input/MouseManager.h"
#include "input/InputManager.h"
#include "ui/DebugUI.h"
#include "entities/EntityManager.h"
#include "managers/StateManager.h"
#include "editor/Editor.h"
#include "map/Camera.h"
#include "tools/MapParser.h"
#include "ui/GameUI.h"
#include "ui/MenuUI.h"
#include "tools/timer/TimerCallback.h"
#include "particles/ParticleManager.h"
#include "renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static GameLoop* game_loop;
		static Assets* assets;
		static StateManager* state;

		static Map* map;
		static Camera* camera;

		static MouseManager* mouse;
		static InputManager* input;

		static EntityManager* entity_manager;

		static ParticleManager* particles;

		static Renderer* renderer;

		static MapParser* map_parser;
		static TimerCallback* timer;

		static DebugUI* debug_ui;
		static GameUI* game_ui;
		static MenuUI* menu_ui;

		static Editor* editor;

		void initiate();
};

#endif