#include "BufferObject.h"
#include <iostream>

BufferObject::BufferObject() {
	vertex_data = new VertexPoint[4];
	index_data = new GLuint[4] {0, 1, 2, 3};

	glGenBuffers(1, &vertex_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_id);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexPoint), vertex_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glGenBuffers(1, &index_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), index_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void BufferObject::free() {
	glDeleteBuffers(1, &vertex_id);
	glDeleteBuffers(1, &index_id);
}

BufferObject::~BufferObject() {
	free();
}