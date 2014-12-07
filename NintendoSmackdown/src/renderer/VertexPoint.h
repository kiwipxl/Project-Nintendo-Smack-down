#ifndef VERTEX_POINT_H
#define VERTEX_POINT_H

#include "../tools/Point2DF.h"
#include "../tools/RGBA.h"

struct VertexPoint {

	Point2DF pos;
	Point2DF uv;
	RGBA colour;
};

#endif