#ifndef COLLISION_H
#define COLLISION_H

#include "../tools/Universal.h"
#include "Node.h"

class Collision {

	public:
		Collision();

		static Universe* universe;

		static Node* collideright(float x, float y);
		static Node* collideleft(float x, float y);
		static Node* collideup(float x, float y);
		static Node* collidedown(float x, float y);
};

#endif