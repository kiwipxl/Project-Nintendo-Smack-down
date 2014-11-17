#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "managers/WindowManager.h"
#include "managers/Assets.h"
#include "GameLoop.h"
#include "map/Map.h"
#include "tools/Point2D.h"
#include "tools/ImageTools.h"
#include "input/MouseManager.h"
#include "input/KeyboardManager.h"
#include "ui/UIManager.h"
#include "entities/EntityManager.h"
#include "managers/StateManager.h"
#include "editor/Editor.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static GameLoop* gameloop;
		static Assets* assets;
		static StateManager* state;

		static Map* map;

		static MouseManager* mouse;
		static KeyboardManager* keyboard;

		static EntityManager* entitymanager;

		static ImageTools* imagetools;

		static UIManager* uimanager;

		static Editor* editor;

		void initiate();
};

#endif