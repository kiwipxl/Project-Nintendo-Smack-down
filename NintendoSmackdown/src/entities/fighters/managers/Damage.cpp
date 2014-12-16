#include "Damage.h"
#include <iostream>
#include "../../../map/Map.h"
#include "../../EntityManager.h"
#include "../../../ui/GameUI.h"
#include "../../../particles/ParticleManager.h"

class Universe {

	public:
		static Map* map;
		static EntityManager* entity_manager;
		static GameUI* game_ui;
		static ParticleManager* particles;
};

Damage::Damage(Fighter* parent) {
	dealt_damage = false;
	health = 0;
	base_parent = parent;
}

/**
updates the damage
**/
void Damage::update_damage() {
	for (Fighter* f : base_universe->entity_manager->fighters) {
		for (Fighter* otherf : base_universe->entity_manager->fighters) {
			if (f != otherf) {
				if (f->pos.x >= otherf->pos.x - 48 && f->pos.x <= otherf->pos.x + 48) {
					if (f->pos.y >= otherf->pos.y - 64 && f->pos.y <= otherf->pos.y + 64) {
						if (!f->dealt_damage && !otherf->invincible) {
							force_x = 0; force_y = 0;
							int damage = 0;
							if (f->current_move == f->moves.PUNCH) {
								force_x = .2f; force_y = -1;
								f->dealt_damage = true;
								damage = 5;
							}else if (f->current_move == f->moves.KICK) {
								force_x = .2f; force_y = -2;
								f->dealt_damage = true;
								damage = 5;
							}else if (f->current_move == f->moves.RAPID_PUNCH) {
								force_x = .1f; force_y = -1;
								f->dealt_damage = true;
								damage = 2;
							}else if (f->current_move == f->moves.HAMMER_PUNCH) {
								force_x = .2f; force_y = -1;
								f->dealt_damage = true;
								damage = 2;
							}else if (f->current_move == f->moves.HAMMER_PUNCH_UP) {
								force_x = 1; force_y = -4;
								f->dealt_damage = true;
								damage = 5;
							}else if (f->current_move == f->moves.HAMMER_COMBO_PUNCH) {
								force_x = .1f; force_y = 4;
								f->dealt_damage = true;
								damage = 5;
							}else if (f->current_move == f->moves.DASH_ATTACK) {
								force_x = 3; force_y = -2.5f;
								f->dealt_damage = true;
								damage = 7;
							}else if (f->current_move == f->moves.SLIDE_ATTACK) {
								force_x = 3.5f; force_y = -2.5f;
								f->dealt_damage = true;
								damage = 8;
							}else if (f->current_move == f->moves.AIR_DOWN_KICK) {
								force_y = 5;
								f->dealt_damage = true;
								damage = 11;
							}else if (f->current_move == f->moves.AIR_KNEE) {
								force_x = 4; force_y = -3;
								f->dealt_damage = true;
								damage = 12;
							}else if (f->current_move == f->moves.AIR_SOMERSAULT) {
								force_y = -3.5f;
								f->dealt_damage = true;
								damage = 11;
							}else if (f->current_move == f->moves.AIR_KICK) {
								force_x = 2.5f; force_y = -4;
								f->dealt_damage = true;
								damage = 10;
							}else if (f->current_move == f->moves.HAMMER_SLAM_DOWN) {
								force_x = 0; force_y = 4;
								f->dealt_damage = true;
								damage = 5;
							}else if (f->current_move == f->moves.HAMMER_SLAM) {
								force_x = 0; force_y = -6;
								f->dealt_damage = true;
								damage = 10;
							}
							if (force_x != 0 || force_y != 0) {
								otherf->add_flip_force(f->flip, force_x, force_y);
							}
							otherf->health += damage;

							base_universe->game_ui->update_damage_text(otherf->id, otherf->health);

							if (f->dealt_damage && damage != 0) {
								base_universe->particles->create_particle_chunk(
										new ParticleEmitter(otherf->pos.x + 80, otherf->pos.y + 64, 
										0, damage, damage, true), BLOOD);
							}
						}
					}
				}
			}
		}
	}
}