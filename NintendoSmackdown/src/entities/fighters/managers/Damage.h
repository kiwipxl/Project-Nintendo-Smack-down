#ifndef DAMAGE_H
#define DAMAGE_H

#include "../../../map/Node.h"
#include "../moves/CaptainFalcon.h"

class Universe;

class Damage {

	public:
		Damage();

		//health
		float health;

		//damage
		bool dealtdamage;

		/**
		updates the damage
		**/
		void updatedamage();

	private:
		//universe
		Universe* duniverse;

		//temp force
		float forcex;
		float forcey;
};

#endif