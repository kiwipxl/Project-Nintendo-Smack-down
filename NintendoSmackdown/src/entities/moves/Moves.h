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

		vector<int> moveframes;

	protected:
		int MOVECOUNT = 14;
};

#endif