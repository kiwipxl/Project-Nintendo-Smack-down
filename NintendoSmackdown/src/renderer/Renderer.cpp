#include "Renderer.h"
#include <iostream>
#include "../managers/WindowManager.h"

class Universe {

	public:
		static WindowManager* win_manager;
};

Renderer::Renderer() {

}

void Renderer::render(Texture* texture, SDL_Rect* src_rect, SDL_Rect* rect) {
	if (texture->created) {
		if (rect->x + rect->w < 0 || rect->y + rect->h < 0 || 
			rect->x > universe->win_manager->screen_width || rect->y > universe->win_manager->screen_height) {
			return;
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(rect->x, rect->y, 0);
		glScalef(rect->w / texture->width, rect->h / texture->height, 1);

		draw_buffer(texture, set_buffer(texture, src_rect));

		++render_calls;
	}
}

void Renderer::render_transform(Texture* texture, SDL_Rect* src_rect, SDL_Rect* rect,
								float angle, SDL_Point* origin, SDL_RendererFlip flip) {
	if (texture->created) {
		if (rect->x + rect->w < 0 || rect->y + rect->h < 0 ||
			rect->x > universe->win_manager->screen_width || rect->y > universe->win_manager->screen_height) {
			return;
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(rect->x + origin->x, rect->y + origin->y, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-origin->x, -origin->y, 0);
		switch (flip) {
			case SDL_FLIP_NONE:
				glScalef(rect->w / texture->width, rect->h / texture->height, 1);
				break;
			case SDL_FLIP_HORIZONTAL:
				glTranslatef(origin->x * 2, 0, 0);
				glScalef(-rect->w / texture->width, rect->h / texture->height, 1);
				break;
			case SDL_FLIP_VERTICAL:
				glTranslatef(0, origin->y * 2, 0);
				glScalef(rect->w / texture->width, -rect->h / texture->height, 1);
				break;
		}

		draw_buffer(texture, set_buffer(texture, src_rect));

		++transform_render_calls;
	}
}

bool Renderer::set_buffer(Texture* texture, SDL_Rect* src_rect) {
	VertexPoint* v = texture->buffer_object->vertex_data;

	SDL_Rect* last_s_r = &texture->last_src_rect;

	float uv_x = 0; float uv_y = 0; float uv_w = 1; float uv_h = 1;
	if (src_rect != NULL) {
		uv_x = src_rect->x / texture->width; uv_y = src_rect->y / texture->height;
		uv_w = src_rect->w / texture->width; uv_h = src_rect->h / texture->height;
	}

	bool has_changed = false;
	if (src_rect == NULL || 
		last_s_r->x != src_rect->x || last_s_r->y != src_rect->y ||
		last_s_r->w != src_rect->w || last_s_r->h != src_rect->h) {
		v[0].uv.x = uv_x;					v[0].uv.y = uv_y;
		v[1].uv.x = uv_x + uv_w;			v[1].uv.y = uv_y;
		v[2].uv.x = uv_x + uv_w;			v[2].uv.y = uv_y + uv_h;
		v[3].uv.x = uv_x;					v[3].uv.y = uv_y + uv_h;
		has_changed = true;

		if (src_rect != NULL) { texture->last_src_rect = *src_rect; }
	}
	
	if (v[1].pos.x != texture->width || v[2].pos.x != texture->width || 
		v[2].pos.y != texture->height || v[3].pos.y != texture->height) {
		v[0].pos.x = 0;						v[0].pos.y = 0;
		v[1].pos.x = texture->width;		v[1].pos.y = 0;
		v[2].pos.x = texture->width;		v[2].pos.y = texture->height;
		v[3].pos.x = 0;						v[3].pos.y = texture->height;

		has_changed = true;
	}

	if (v[0].colour.r != texture->last_colour.r ||
		v[0].colour.g != texture->last_colour.g ||
		v[0].colour.b != texture->last_colour.b || 
		v[0].colour.a != texture->last_colour.a) {
		has_changed = true;
		cout << "id: " << v[0].colour.a << "\n";
		texture->last_colour.r = v[0].colour.r;
		texture->last_colour.g = v[0].colour.g;
		texture->last_colour.b = v[0].colour.b;
		texture->last_colour.a = v[0].colour.a;
	}

	return has_changed;
}

void Renderer::draw_buffer(Texture* texture, bool upload_buffer) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	{
		glBindBuffer(GL_ARRAY_BUFFER, texture->buffer_object->vertex_id);
		if (upload_buffer) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(VertexPoint), texture->buffer_object->vertex_data);
			++vertices_uploaded;
		}

		glTexCoordPointer(2, GL_FLOAT, sizeof(VertexPoint), (GLvoid*)offsetof(VertexPoint, uv));
		glVertexPointer(2, GL_FLOAT, sizeof(VertexPoint), (GLvoid*)offsetof(VertexPoint, pos));
		glColorPointer(4, GL_FLOAT, sizeof(VertexPoint), (GLvoid*)offsetof(VertexPoint, colour));

		glBindBuffer(GL_ARRAY_BUFFER, texture->buffer_object->index_id);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, texture->buffer_object->index_data);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	++total_render_calls;
}