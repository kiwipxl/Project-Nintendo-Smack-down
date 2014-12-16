#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL.h>
#include "../../tools/Universal.h"
#include "managers/Movement.h"
#include "managers/Damage.h"

enum FighterType {
	PLAYER,
	EASYAI,
	MEDIUMAI,
	HARDAI
};

class ParticleController;

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
		bool enable_camera_view;
		int width;
		int height;

		void update();

	private:
		float alpha_colour;
		ParticleController* blood_particles;
		int offset_x = 0;
		int offset_y = 0;
};

#endif