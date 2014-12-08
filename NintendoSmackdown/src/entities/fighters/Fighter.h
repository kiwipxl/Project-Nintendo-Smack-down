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
		Fighter(int x, int y, int c_player_id, int c_id, FighterName f_name, FighterType f_type);

		int id;
		int player_id;
		FighterName name;
		FighterType type;
		bool respawning;
		bool invincible;
		Texture* texture;

		void update();

	private:
		float alpha_colour;
};

#endif