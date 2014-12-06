#include "Fighter.h"
#include <iostream>
#include "../../managers/WindowManager.h"
#include "../../map/Map.h"
#include "../../managers/Assets.h"
#include "../../input/InputManager.h"
#include "../../map/Collision.h"
#include "../../map/Camera.h"
#include "../../map/Tiles.h"
#include "../EntityManager.h"
#include "../../tools/timer/TimerCallback.h"
#include "../../ui/GameUI.h"
#include "../../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Map* map;
		static Assets* assets;
		static InputManager* input;
		static Camera* camera;
		static EntityManager* entity_manager;
		static TimerCallback* timer;
		static GameUI* game_ui;
		static Renderer* renderer;
};

Fighter::Fighter(int x, int y, FighterName fname, FighterType ftype) : Movement(this), Damage(this) {
	//setup the moves from the inputted fighter
	moves = CaptainFalcon();

	pos.x = x; pos.y = y;
	name = fname; type = ftype;
	respawning = false;
	invincible = false;

	texture = new Texture();
	texture->create_texture(universe->assets->fighter_sheets[0]->s);
	animator = new Animator(texture, &src_rect, 64, 64, 5, true, true);
	update_move(moves.JUMP, 10, false);
	alpha_colour = 0;
}

void Fighter::update() {
	if (type == PLAYER) {
		left_key = universe->input->left_key[playerid];
		right_key = universe->input->right_key[playerid];
		up_key = universe->input->up_key[playerid];
		down_key = universe->input->down_key[playerid];
		a_key = universe->input->a_key[playerid];
		b_key = universe->input->b_key[playerid];
	}else {
		//TODO implement ai here
	}

	if (invincible) {
		//SDL_SetTextureAlphaMod(texture->t, 140 + (sin(alpha_colour / 6) * 50));
		++alpha_colour;
	}

	if (!respawning) {
		update_movement();
		update_damage();
		rect.x = pos.x + universe->camera->x + universe->camera->get_offset_x(pos.x);
		rect.y = pos.y + universe->camera->y + universe->camera->get_offset_y(pos.y);
		rect.w = 64 * universe->camera->scale; rect.h = 64 * universe->camera->scale;
		origin.x = rect.w / 2; origin.y = rect.h / 2;
		universe->renderer->render_transform(texture, &src_rect, &rect, rotation, &origin, flip);

		if (pos.x < universe->camera->min_bounds_x - 400 || pos.x > universe->camera->max_bounds_x + 400 || 
			pos.y < universe->camera->min_bounds_y - 250 || pos.y > universe->camera->max_bounds_y + 250) {
			respawning = true;
			health = 0;
			universe->game_ui->update_damage_text(id, health);

			//respawn after 1.5 seconds
			universe->timer->set_timer([this](void) {
				current_move = moves.IDLE;
				rotation = 0;
				gravity = 0;
				respawning = false;
				pos.x = 100 + (rand() % (universe->map->map_width - 400));
				pos.y = -150;
				invincible = true;
				alpha_colour = 0;
				//turn off invincibility after 1 second
				universe->timer->set_timer([this](void) { invincible = false; //SDL_SetTextureAlphaMod(texture->t, 255);
				}, 2000);
			}, 1500);
		}
	}
}