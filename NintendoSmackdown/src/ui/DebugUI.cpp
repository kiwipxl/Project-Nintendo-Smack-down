#include "DebugUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../managers/WindowManager.h"
#include "../GameLoop.h"
#include "../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static GameLoop* game_loop;
		static Renderer* renderer;
};

void DebugUI::create() {
	fps_text = new Text(5, 0, 20, { 0, 0, 0 }, "", true);
	render_text = new Text(5, 25, 14, { 0, 0, 0 }, "", true);
	transform_render_text = new Text(5, 42, 14, { 0, 0, 0 }, "", true);
	vertices_uploaded_text = new Text(5, 60, 14, { 0, 0, 0 }, "", true);
	total_renders_text = new Text(5, 80, 14, { 0, 0, 0 }, "", true);
	std::cout << "debug_ui created\n";
}

void DebugUI::update() {
	fps_text->render();
	render_text->render();
	transform_render_text->render();
	vertices_uploaded_text->render();
	total_renders_text->render();
}

void DebugUI::update_fps_text(int fps) {
	std::string fps_str = "Fps: ";
	fps_str += std::to_string(fps);
	fps_text->render_text(fps_str, true);
}

void DebugUI::update_render_info() {
	std::string normal_render_str = "Render calls: ";
	normal_render_str += std::to_string(universe->renderer->render_calls);
	render_text->render_text(normal_render_str, true);

	std::string transform_render_str = "Transformed render calls: ";
	transform_render_str += std::to_string(universe->renderer->transform_render_calls);
	transform_render_text->render_text(transform_render_str, true);

	std::string vertices_uploaded_str = "Vertices uploaded to GPU: ";
	vertices_uploaded_str += std::to_string(universe->renderer->vertices_uploaded);
	vertices_uploaded_text->render_text(vertices_uploaded_str, true);

	std::string total_renders_str = "Total render calls: ";
	total_renders_str += std::to_string(universe->renderer->total_render_calls);
	total_renders_text->render_text(total_renders_str, true);
}

void DebugUI::remove() {
	delete fps_text;
	delete render_text;
	delete transform_render_text;
	delete vertices_uploaded_text;
	delete total_renders_text;
}