#ifndef CAPTAIN_FALCON_H
#define CAPTAIN_FALCON_H

#include "Moves.h"

class CaptainFalcon : public Moves {

	public:
		CaptainFalcon() {
			for (int i = 0; i < MOVE_COUNT; ++i) {
				move_frames.push_back(0);
			}

			IDLE = 0;
			TAUNT = 1;
			JUMP = 2;
			LAND = 3;
			RUN = 4;
			KICK = 5;
			PUNCH = 6;
			DOUBLE_JUMP = 7;
			SHIELD = 8;
			CROUCH = 9;
			EDGE_GRAB = 10;
			RAPID_PUNCH = 11;
			DASH_ATTACK = 12;
			SLIDE_ATTACK = 13;
			AIR_KNEE = 14;
			HIT = 15;
			AIR_DOWN_KICK = 16;
			AIR_LAND = 17;
			AIR_SOMERSAULT = 18;
			AIR_KICK = 19;

			RUN_FPS = 15;
			DASH_ATTACK_FPS = 10;
			AIR_LAND_FPS = 4;
			SLIDE_ATTACK_FPS = 10;
			AIR_KICK_FPS = 12;

			move_frames[IDLE] = 4;
			move_frames[TAUNT] = 4;
			move_frames[JUMP] = 3;
			move_frames[LAND] = 3;
			move_frames[RUN] = 8;
			move_frames[KICK] = 4;
			move_frames[PUNCH] = 2;
			move_frames[DOUBLE_JUMP] = 4;
			move_frames[SHIELD] = 3;
			move_frames[CROUCH] = 1;
			move_frames[EDGE_GRAB] = 2;
			move_frames[RAPID_PUNCH] = 2;
			move_frames[DASH_ATTACK] = 4;
			move_frames[SLIDE_ATTACK] = 6;
			move_frames[AIR_KNEE] = 5;
			move_frames[HIT] = 1;
			move_frames[AIR_DOWN_KICK] = 4;
			move_frames[AIR_LAND] = 1;
			move_frames[AIR_SOMERSAULT] = 4;
			move_frames[AIR_KICK] = 3;
		}
};

#endif