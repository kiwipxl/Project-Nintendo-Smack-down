#include "Fighter.h"
#include <iostream>
#include "../../managers/WindowManager.h"
#include "../../map/Map.h"
#include "../../managers/Assets.h"
#include "../../input/KeyboardManager.h"
#include "../../map/Collision.h"
#include "../../map/Camera.h"
#include "../../map/Tiles.h"
#include "../EntityManager.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Map* map;
		static Assets* assets;
		static KeyboardManager* keyboard;
		static Camera* camera;
		static EntityManager* entity_manager;
};

Fighter::Fighter(int x, int y, FighterName fname, FighterType ftype) : Movement(this), Damage(this) {
	pos.x = x; pos.y = y;
	name = fname; type = ftype;
	id = universe->entity_manager->fighters.size();
}

void Fighter::update() {
	if (type == PLAYER) {
		left_key_down = universe->keyboard->left_key_down;
		right_key_down = universe->keyboard->right_key_down;
		up_key_down = universe->keyboard->up_key_down;
		down_key_down = universe->keyboard->down_key_down;
		a_key_down = universe->keyboard->a_key_down;
		b_key_down = universe->keyboard->b_key_down;
	}else {

	}
	update_movement();
	update_damage();
	rect.x = pos.x + universe->camera->x + universe->camera->get_offset_x(pos.x);
	rect.y = pos.y + universe->camera->y + universe->camera->get_offset_y(pos.y);
	rect.w = 64 * universe->camera->scale; rect.h = 64 * universe->camera->scale;
	origin.x = rect.w / 2; origin.y = rect.h / 2;
	SDL_RenderCopyEx(universe->win_manager->renderer, animation_sheet->t, &src_rect, &rect, rotation, &origin, flip);
}