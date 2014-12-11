#include "ParticleRenderer.h"
#include <iostream>
#include "../../managers/WindowManager.h"
#include "../ParticleController.h"
#include "../../managers/Assets.h"
#include "../../renderer/Renderer.h"
#include "../../map/Camera.h"
#include "../ParticleManager.h"
#include <algorithm>

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static Renderer* renderer;
		static Camera* camera;
		static ParticleManager* particles;
};

void ParticleRenderer::create_texture() {
	texture = new Texture();
	texture->create_texture(universe->assets->particle_sheet->s, parent->max_particles * 4);

	switch (parent->type) {
		case CLOUD:
			src_rect.x = 0; src_rect.y = 0;
			src_rect.w = 256; src_rect.h = 256;
			break;
		case BLOOD:
			src_rect.x = 256; src_rect.y = 0;
			src_rect.w = 64; src_rect.h = 64;
			break;
	}

	matrices = new GLfloat[parent->max_particles * 16];
	glGetFloatv(GL_MODELVIEW, matrices);

	VertexPoint* v = texture->buffer_object->vertex_data;
	GLuint* i = texture->buffer_object->index_data;

	float uv_x = 0; float uv_y = 0; float uv_w = 1; float uv_h = 1;
	uv_x = src_rect.x / texture->width; uv_y = src_rect.y / texture->height;
	uv_w = src_rect.w / texture->width; uv_h = src_rect.h / texture->height;

	for (int n = 0; n < parent->max_particles * 4; n += 4) {
		v[n].uv.x = uv_x;						v[n].uv.y = uv_y;
		v[n + 1].uv.x = uv_x + uv_w;			v[n + 1].uv.y = uv_y;
		v[n + 2].uv.x = uv_x + uv_w;			v[n + 2].uv.y = uv_y + uv_h;
		v[n + 3].uv.x = uv_x;					v[n + 3].uv.y = uv_y + uv_h;
	}

	for (int n = 0; n < parent->max_particles * 4; ++n) {
		v[n].colour.r = 1; v[n].colour.g = 1; v[n].colour.b = 1; v[n].colour.a = 1;
	}

	for (int n = 0; n < parent->max_particles * 4; ++n) {
		i[n] = n;
	}

	universe->renderer->draw_buffer(texture, true);
}

void ParticleRenderer::update_renderer() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glMultMatrixf(matrices);

	VertexPoint* v = texture->buffer_object->vertex_data;
	int x = 0; int y = 0;
	int s_x = src_rect.w * universe->camera->scale;
	int s_y = src_rect.h * universe->camera->scale;
	for (Particle* &p : parent->particles) {
		int id = p->v_id;
		p->update();
		if (!p->removed) {
			x = p->pos.x - (p->origin.x * p->scale); y = p->pos.y - (p->origin.y * p->scale);

			if (x + (s_x * p->scale) < 0 || y + (s_y * p->scale) < 0 || 
				x > universe->win_manager->screen_width || y > universe->win_manager->screen_height) {
				for (int i = 0; i < 4; ++i) {
					v[id + i].pos.x = 0;
					v[id + i].pos.y = 0;
				}
				continue;
			}

			v[id].pos.x = x;								v[id].pos.y = y;
			v[id + 1].pos.x = x + (s_x * p->scale);			v[id + 1].pos.y = y;
			v[id + 2].pos.x = x + (s_x * p->scale);			v[id + 2].pos.y = y + (s_y * p->scale);
			v[id + 3].pos.x = x;							v[id + 3].pos.y = y + (s_y * p->scale);

			++universe->particles->particles_drawn;
		}else {
			for (int i = 0; i < 4; ++i) {
				v[id + i].pos.x = 0;
				v[id + i].pos.y = 0;
			}
			p = nullptr;
		}
	}

	parent->particles.erase(std::remove(parent->particles.begin(), parent->particles.end(), nullptr), parent->particles.end());

	universe->renderer->draw_buffer(texture, true);
}