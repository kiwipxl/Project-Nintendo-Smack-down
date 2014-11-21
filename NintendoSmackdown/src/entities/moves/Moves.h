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
		int DOUBLEJUMP;
		int SHIELD;
		int CROUCH;
		int EDGEGRAB;

		vector<int> moveframes;

	protected:
		int MOVECOUNT = 11;
};

#endif