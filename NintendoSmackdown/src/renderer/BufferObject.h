#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <SDL.h>
#include <glew.h>
#include "VertexPoint.h"

class BufferObject {

	public:
		BufferObject();
		~BufferObject();

		GLuint vertex_id;
		VertexPoint* vertex_data;
		GLuint index_id;
		GLuint* index_data;
};

#endif