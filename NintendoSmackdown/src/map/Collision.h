#ifndef COLLISION_H
#define COLLISION_H

#include "../tools/Universal.h"
#include "Node.h"

class Collision {

	public:
		Collision();

		static Universe* universe;

		static Node* collide_right(float x, float y);
		static Node* collide_left(float x, float y);
		static Node* collide_up(float x, float y);
		static Node* collide_down(float x, float y);
};

#endif