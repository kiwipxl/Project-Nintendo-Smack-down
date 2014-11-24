#include "Damage.h"
#include <iostream>
#include "../../../map/Map.h"
#include "../../EntityManager.h"

class Universe {

	public:
		static Map* map;
		static EntityManager* entitymanager;
};

Damage::Damage() {
	dealtdamage = false;
	health = 0;
}

/**
updates the damage
**/
void Damage::updatedamage() {
	for (Fighter* f : duniverse->entitymanager->fighters) {
		for (Fighter* otherf : duniverse->entitymanager->fighters) {
			if (f != otherf) {
				if (f->pos.x >= otherf->pos.x - 48 && f->pos.x <= otherf->pos.x + 48) {
					if (f->pos.y >= otherf->pos.y - 64 && f->pos.y <= otherf->pos.y + 64) {
						if (!f->dealtdamage) {
							forcex = 0; forcey = 0;
							if (f->currentmove == f->moves.PUNCH) {
								forcex = .2f; forcey = 2;
								f->dealtdamage = true;
								otherf->health += 5;
							}else if (f->currentmove == f->moves.KICK) {
								forcex = .2f; forcey = 2;
								f->dealtdamage = true;
								otherf->health += 5;
							}else if (f->currentmove == f->moves.RAPIDPUNCH) {
								forcex = .1f; forcey = 1;
								f->dealtdamage = true;
								otherf->health += 2;
							}else if (f->currentmove == f->moves.DASHATTACK) {
								forcex = 5; forcey = 5;
								f->dealtdamage = true;
								otherf->health += 7;
							}else if (f->currentmove == f->moves.SLIDEATTACK) {
								forcex = 5.5f; forcey = 5;
								f->dealtdamage = true;
								otherf->health += 8;
							}
							if (forcex != 0 || forcey != 0) {
								if (f->pos.y < otherf->pos.y - 32) { forcey = -forcey; }
								otherf->addflipforce(f->flip, forcex, forcey);
							}
						}
					}
				}
			}
		}
	}
}