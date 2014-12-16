#ifndef MOVES_H
#define MOVES_H

#include <vector>

enum FighterName {
	CAPTAIN_FALCON,
	THOR
};

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

		int HAMMER_PUNCH;
		int HAMMER_PUNCH_UP;
		int HAMMER_COMBO_PUNCH;
		int HAMMER_SLAM_DOWN;
		int HAMMER_SLAM;

		int RUN_FPS;
		int DASH_ATTACK_FPS;
		int AIR_LAND_FPS;
		int SLIDE_ATTACK_FPS;
		int AIR_KICK_FPS;

		std::vector<int> move_frames;
		FighterName name;

	protected:
		int MOVE_COUNT = 25;
};

#endif