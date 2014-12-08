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

Fighter::Fighter(int x, int y, int c_player_id, int c_id, FighterName f_name, FighterType f_type) 
	: Movement(this), Damage(this) {
	//setup the moves from the inputted fighter
	moves = CaptainFalcon();

	player_id = c_player_id;
	id = c_id;

	pos.x = x; pos.y = y;
	name = f_name; type = f_type;
	respawning = false;
	invincible = false;

	texture = new Texture();
	texture->create_texture(universe->assets->fighter_sheets[0]->s);
	animator = new Animator(texture, &src_rect, 64, 64, 5, true, true);
	update_move(moves.JUMP, 10, false);
	alpha_colour = 0;

	if (id == 1) {
		texture->set_colour(0, .5f, 1, 1);
	}
}

void Fighter::update() {
	if (type == PLAYER) {
		left_key = universe->input->left_key[player_id];
		right_key = universe->input->right_key[player_id];
		up_key = universe->input->up_key[player_id];
		down_key = universe->input->down_key[player_id];
		a_key = universe->input->a_key[player_id];
		b_key = universe->input->b_key[player_id];
	}else {
		//TODO implement ai here
	}

	if (invincible) {
		texture->set_colour(1, 1, 1, .25f + ((sin(alpha_colour / 4) + 1) / 2.5f));
		if (id == 1) {
			texture->set_colour(0, .5f, 1, .25f + ((sin(alpha_colour / 4) + 1) / 2.5f));
		}
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
				universe->timer->set_timer([this](void) { invincible = false; texture->set_colour(1, 1, 1, 1);
					if (id == 1) {
						texture->set_colour(0, .5f, 1, 1);
					}
				}, 2500);
			}, 1500);
		}
	}
}