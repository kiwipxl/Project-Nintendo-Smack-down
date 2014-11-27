#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL.h>
#include "../../tools/Universal.h"
#include "managers/Movement.h"
#include "managers/Damage.h"

enum FighterName {
	CAPTAIN_FALCON
};

enum FighterType {
	PLAYER,
	EASYAI,
	MEDIUMAI,
	HARDAI
};

class Fighter : Universal, public Movement, public Damage {

	public:
		Fighter(int x, int y, FighterName fname, FighterType ftype);

		int id;
		int playerid;
		FighterName name;
		FighterType type;

		void update();
};

#endif