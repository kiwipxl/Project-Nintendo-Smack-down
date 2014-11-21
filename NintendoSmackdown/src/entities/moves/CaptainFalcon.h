#ifndef CAPTAIN_FALCON_H
#define CAPTAIN_FALCON_H

#include "Moves.h"

class CaptainFalcon : public Moves {

	public:
		CaptainFalcon() {
			for (int i = 0; i < MOVECOUNT; ++i) {
				moveframes.push_back(0);
			}

			IDLE = 0;
			TAUNT = 1;
			JUMP = 2;
			LAND = 3;
			RUN = 4;
			KICK = 5;
			PUNCH = 6;
			DOUBLEJUMP = 7;
			SHIELD = 8;
			CROUCH = 9;
			EDGEGRAB = 10;
			RAPIDPUNCH = 11;
			DASHATTACK = 12;

			moveframes[IDLE] = 4;
			moveframes[TAUNT] = 4;
			moveframes[JUMP] = 3;
			moveframes[LAND] = 3;
			moveframes[RUN] = 8;
			moveframes[KICK] = 4;
			moveframes[PUNCH] = 2;
			moveframes[DOUBLEJUMP] = 4;
			moveframes[SHIELD] = 3;
			moveframes[CROUCH] = 1;
			moveframes[EDGEGRAB] = 2;
			moveframes[RAPIDPUNCH] = 2;
			moveframes[DASHATTACK] = 3;
		}
};

#endif