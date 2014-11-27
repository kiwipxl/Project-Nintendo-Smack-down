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
		int RAPID_PUNCH;
		int DOUBLE_JUMP;
		int SHIELD;
		int CROUCH;
		int EDGE_GRAB;
		int DASH_ATTACK;
		int SLIDE_ATTACK;
		int AIR_KNEE;
		int HIT;
		int AIR_DOWN_KICK;
		int AIR_LAND;
		int AIR_SOMERSAULT;
		int AIR_KICK;

		std::vector<int> move_frames;

	protected:
		int MOVE_COUNT = 20;
};

#endif