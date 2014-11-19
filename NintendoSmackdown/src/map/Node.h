#ifndef NODE_H
#define NODE_H

#include "../tools/Point2D.h"
#include "Tiles.h"

class Node {

	public:
		Node() {
			solid = false;
		}

		Type* type;
		bool solid;
};

#endif