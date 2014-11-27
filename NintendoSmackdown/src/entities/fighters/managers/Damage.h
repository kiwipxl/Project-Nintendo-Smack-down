#ifndef DAMAGE_H
#define DAMAGE_H

#include "../../../map/Node.h"
#include "../moves/CaptainFalcon.h"
#include "FighterBase.h"

class Damage : FighterBase {

	public:
		Damage(Fighter* parent);

		//health
		float health;

		//damage
		bool dealt_damage;

		/**
		updates the damage
		**/
		void update_damage();

	private:
		//temp force
		float force_x;
		float force_y;
};

#endif