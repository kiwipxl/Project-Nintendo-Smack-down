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
#include "../../particles/ParticleManager.h"
#include "moves/Thor.h"

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
		static ParticleManager* particles;
};

Fighter::Fighter(int x, int y, int c_player_id, int c_id, FighterName f_name, FighterType f_type) 
	: Movement(this), Damage(this) {
	//setup the moves from the inputted fighter
	texture = new Texture();
	switch (f_name) {
		case CAPTAIN_FALCON:
			moves = CaptainFalcon();
			moves.name = CAPTAIN_FALCON;
			texture->create_texture(universe->assets->fighter_sheets[0]->s);
			width = 64; height = 64;
			offset_y = 2;
			break;
		case THOR:
			moves = Thor();
			moves.name = THOR;
			texture->create_texture(universe->assets->fighter_sheets[1]->s);
			width = 75; height = 75;
			offset_x = -16; offset_y = -16;
			break;
	}

	player_id = c_player_id;
	id = c_id;

	pos.x = x; pos.y = y;
	name = f_name; type = f_type;
	respawning = false;
	invincible = false;
	enable_camera_view = true;

	animator = new Animator(texture, &src_rect, 64, 64, 5, true, true);
	update_move(moves.JUMP, 10, false);
	alpha_colour = 0;

	r = 1; g = 1; b = 1;
	if (id == 1) {
		r = 0; g = .5f; b = 1;
	}else if (id == 2) {
		r = 1; g = .5f; b = 0;
	}else if (id == 3) {
		r = 0; g = 1; b = .5f;
	}
	texture->set_colour(r, g, b, 1);

	blood_particles = universe->particles->create_particle_chunk(
		new ParticleEmitter(pos.x + 80, pos.y + 64, 10, 1, 4, false), BLOOD);
	blood_particles->max_particles = 0;
}

void Fighter::update() {
	if (health >= 100) {
		blood_particles->max_particles = 4;
		blood_particles->spawn_x = pos.x + 80;
		blood_particles->spawn_y = pos.y + 64;
	}

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
		texture->set_colour(r, g, b,  .25f + ((sin(alpha_colour / 4) + 1) / 2.5f));
		++alpha_colour;
	}

	if (!respawning) {
		update_movement();
		update_damage();
		rect.x = pos.x + universe->camera->x + universe->camera->get_offset_x(pos.x) + offset_x;
		rect.y = pos.y + universe->camera->y + universe->camera->get_offset_y(pos.y) + offset_y;
		rect.w = width * universe->camera->scale; rect.h = height * universe->camera->scale;
		origin.x = rect.w / 2; origin.y = rect.h / 2;
		universe->renderer->render_transform(texture, &src_rect, &rect, rotation, &origin, flip);

		int min_bounds_x = universe->camera->min_bounds_x - 250;
		int max_bounds_x = universe->camera->max_bounds_x + 300;
		int min_bounds_y = universe->camera->min_bounds_y - 250;
		int max_bounds_y = universe->camera->max_bounds_y + 250;
		if (pos.x < min_bounds_x || pos.x > max_bounds_x || pos.y < min_bounds_y || pos.y > max_bounds_y) {
			int p_x = pos.x; int p_y = pos.y;
			if (p_x < min_bounds_x) { p_x = min_bounds_x; }else if (p_x > max_bounds_x) { p_x = max_bounds_x; }
			if (p_y < min_bounds_y) { p_y = min_bounds_y; }else if (p_y > max_bounds_y) { p_y = max_bounds_y; }

			universe->particles->create_particle_chunk(new ParticleEmitter(p_x, p_y, 
																		   0, 250, 250, true), CLOUD);
			universe->particles->create_particle_chunk(new ParticleEmitter(p_x, p_y, 
																		   0, 250, 250, true), BLOOD_CLOUD);

			respawning = true;
			health = 0;
			universe->game_ui->update_damage_text(id, health);

			//respawn after 2.5 seconds
			universe->timer->set_timer([this](void) {
				reset();
				respawning = false;
				enable_camera_view = true;
				pos.x = 100 + (rand() % (universe->map->map_width - 400));
				pos.y = -150;
				invincible = true;
				alpha_colour = 0;
				//turn off invincibility after 1 second
				universe->timer->set_timer([this](void) { invincible = false; texture->set_colour(r, g, b, 1);
				}, 2500);
			}, 2500);

			//turn off camera view after 1.5 seconds
			universe->timer->set_timer([this](void) {
				if (respawning) {
					enable_camera_view = false;
				}
			}, 1500);
		}
	}
}