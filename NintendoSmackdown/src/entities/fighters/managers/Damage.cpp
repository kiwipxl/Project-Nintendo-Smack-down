#include "Damage.h"
#include <iostream>
#include "../../../map/Map.h"
#include "../../EntityManager.h"
#include "../../../ui/GameUI.h"

class Universe {

	public:
		static Map* map;
		static EntityManager* entity_manager;
		static GameUI* game_ui;
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
						if (!f->dealt_damage) {
							force_x = 0; force_y = 0;
							if (f->current_move == f->moves.PUNCH) {
								force_x = .2f; force_y = 1;
								f->dealt_damage = true;
								otherf->health += 5;
							}else if (f->current_move == f->moves.KICK) {
								force_x = .2f; force_y = 2;
								f->dealt_damage = true;
								otherf->health += 5;
							}else if (f->current_move == f->moves.RAPID_PUNCH) {
								force_x = .1f; force_y = 1;
								f->dealt_damage = true;
								otherf->health += 2;
							}else if (f->current_move == f->moves.DASH_ATTACK) {
								force_x = 5; force_y = 2;
								f->dealt_damage = true;
								otherf->health += 7;
							}else if (f->current_move == f->moves.SLIDE_ATTACK) {
								force_x = 5.5f; force_y = 2;
								f->dealt_damage = true;
								otherf->health += 8;
							}else if (f->current_move == f->moves.AIR_DOWN_KICK) {
								force_y = -5;
								f->dealt_damage = true;
								otherf->health += 11;
							}else if (f->current_move == f->moves.AIR_KNEE) {
								force_x = 5; force_y = 1;
								f->dealt_damage = true;
								otherf->health += 12;
							}else if (f->current_move == f->moves.AIR_SOMERSAULT) {
								force_y = 4;
								f->dealt_damage = true;
								otherf->health += 11;
							}else if (f->current_move == f->moves.AIR_KICK) {
								force_x = .5f; force_y = 1;
								f->dealt_damage = true;
								otherf->health += 10;
							}
							if (force_x != 0 || force_y != 0) {
								if (f->pos.y < otherf->pos.y - 32) { force_y = -force_y; }
								otherf->add_flip_force(f->flip, force_x, force_y);
							}
							base_universe->game_ui->update_damage_text(otherf->id, otherf->health);
						}
					}
				}
			}
		}
	}
}