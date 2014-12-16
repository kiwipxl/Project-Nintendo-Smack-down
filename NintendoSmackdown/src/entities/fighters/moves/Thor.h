#ifndef THOR_H
#define THOR_H

#include "Moves.h"

class Thor : public Moves {

	public:
		Thor() {
			for (int i = 0; i < MOVE_COUNT; ++i) {
				move_frames.push_back(0);
			}

			IDLE = 0;
			TAUNT = 1;
			JUMP = 2;
			LAND = 3;
			RUN = 4;
			HAMMER_PUNCH_UP = 5;
			HAMMER_PUNCH = 6;
			DOUBLE_JUMP = 7;
			SHIELD = 8;
			CROUCH = 9;
			EDGE_GRAB = 10;
			HAMMER_COMBO_PUNCH = 11;
			DASH_ATTACK = 12;
			SLIDE_ATTACK = 13;
			AIR_KNEE = 14;
			HIT = 15;
			HAMMER_SLAM_DOWN = 16;
			AIR_LAND = 17;
			AIR_SOMERSAULT = 18;
			AIR_KICK = 19;
			HAMMER_SLAM = 20;

			RUN_FPS = 20;
			DASH_ATTACK_FPS = 20;
			AIR_LAND_FPS = 10;
			SLIDE_ATTACK_FPS = 15;
			AIR_KICK_FPS = 20;

			move_frames[IDLE] = 8;
			move_frames[TAUNT] = 4;
			move_frames[JUMP] = 3;
			move_frames[LAND] = 3;
			move_frames[RUN] = 12;
			move_frames[HAMMER_PUNCH_UP] = 8;
			move_frames[HAMMER_PUNCH] = 6;
			move_frames[DOUBLE_JUMP] = 6;
			move_frames[SHIELD] = 3;
			move_frames[CROUCH] = 1;
			move_frames[EDGE_GRAB] = 1;
			move_frames[HAMMER_COMBO_PUNCH] = 10;
			move_frames[DASH_ATTACK] = 9;
			move_frames[SLIDE_ATTACK] = 9;
			move_frames[AIR_KNEE] = 7;
			move_frames[HIT] = 1;
			move_frames[HAMMER_SLAM_DOWN] = 3;
			move_frames[HAMMER_SLAM] = 7;
			move_frames[AIR_LAND] = 3;
			move_frames[AIR_SOMERSAULT] = 8;
			move_frames[AIR_KICK] = 7;
		}
};

#endif