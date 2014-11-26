#ifndef MOVES_H
#define MOVES_H

#include <vector>

class Moves {

	public:
		Moves() { }

		int IDLE;
		int TAUNT;
		int JUMP;
		int LAND;
		int RUN;
		int KICK;
		int PUNCH;
		int RAPIDPUNCH;
		int DOUBLEJUMP;
		int SHIELD;
		int CROUCH;
		int EDGEGRAB;
		int DASHATTACK;
		int SLIDEATTACK;
		int AIRKNEE;
		int HIT;
		int AIRDOWNKICK;
		int AIRLAND;
		int AIRSOMERSAULT;
		int AIRKICK;

		std::vector<int> moveframes;

	protected:
		int MOVECOUNT = 20;
};

#endif