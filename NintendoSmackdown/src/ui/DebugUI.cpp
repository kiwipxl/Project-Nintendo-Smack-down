#include "DebugUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../managers/WindowManager.h"
#include "../GameLoop.h"
#include "../renderer/Renderer.h"
#include "../input/InputManager.h"
#include "../particles/ParticleManager.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static GameLoop* game_loop;
		static Renderer* renderer;
		static InputManager* input;
		static ParticleManager* particles;
};

void DebugUI::create() {
	debugging = true;
	fps_text = new Text(5, 0, 15, { 0, 0, 0 }, "", true);
	render_text = new Text(5, 25, 12, { 0, 0, 0 }, "", true);
	transform_render_text = new Text(5, 42, 12, { 0, 0, 0 }, "", true);
	vertices_uploaded_text = new Text(5, 60, 12, { 0, 0, 0 }, "", true);
	total_renders_text = new Text(5, 80, 12, { 0, 0, 0 }, "", true);
	particles_drawn_text = new Text(5, 99, 12, { 0, 0, 0 }, "", true);
	particles_uploaded_text = new Text(5, 118, 12, { 0, 0, 0 }, "", true);
	particle_chunks_text = new Text(5, 137, 12, { 0, 0, 0 }, "", true);
	std::cout << "debug_ui created\n";
}

void DebugUI::update() {
	if (debugging) {
		fps_text->render();
		render_text->render();
		transform_render_text->render();
		vertices_uploaded_text->render();
		total_renders_text->render();
		particles_drawn_text->render();
		particles_uploaded_text->render();
		particle_chunks_text->render();
	}

	if (universe->input->d_key[0]->pressed) {
		debugging = !debugging;
	}
}

void DebugUI::update_fps_text(int fps) {
	std::string fps_str = "Fps: ";
	fps_str += std::to_string(fps);
	fps_text->render_text(fps_str, true);
}

void DebugUI::update_render_info() {
	if (debugging) {
		std::string str;
		str = "Render calls: ";
		str += std::to_string(universe->renderer->render_calls);
		render_text->render_text(str, true);

		str = "Transformed render calls: ";
		str += std::to_string(universe->renderer->transform_render_calls);
		transform_render_text->render_text(str, true);

		str = "Vertices uploaded: ";
		str += std::to_string(universe->renderer->vertices_uploaded);
		vertices_uploaded_text->render_text(str, true);

		str = "Total render calls: ";
		str += std::to_string(universe->renderer->total_render_calls);
		total_renders_text->render_text(str, true);

		str = "Particles drawn: ";
		str += std::to_string(universe->particles->particles_drawn);
		particles_drawn_text->render_text(str, true);

		str = "Particles uploaded: ";
		str += std::to_string(universe->particles->particles_uploaded);
		particles_uploaded_text->render_text(str, true);

		str = "Particle chunks: ";
		str += std::to_string(universe->particles->particle_chunks.size());
		particle_chunks_text->render_text(str, true);
	}
}

void DebugUI::remove() {
	delete fps_text;
	delete render_text;
	delete transform_render_text;
	delete vertices_uploaded_text;
	delete total_renders_text;
	delete particles_drawn_text;
	delete particles_uploaded_text;
	delete particle_chunks_text;
}