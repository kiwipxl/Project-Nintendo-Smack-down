#ifndef NODE_H
#define NODE_H

#include "../tools/Point2D.h"
#include "Tiles.h"

class Node {

	public:
		Node() {
			solid = false;
			edgeempty = true;
		}

		Type* type;
		bool solid;
		bool edgeempty;
};

#endif