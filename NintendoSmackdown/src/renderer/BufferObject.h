#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <SDL.h>
#include <glew.h>
#include <vector>
#include "VertexPoint.h"

class BufferObject {

	public:
		BufferObject(int c_buffer_size = 4);
		~BufferObject();

		int buffer_size;
		GLuint vertex_id;
		VertexPoint* vertex_data;
		GLuint index_id;
		GLuint* index_data;

		void free();
};

#endif