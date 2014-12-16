#include "Editor.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../input/InputManager.h"
#include "../input/MouseManager.h"
#include "../managers/Assets.h"
#include "../Map/Camera.h"
#include "../Managers/StateManager.h"
#include "../renderer/Renderer.h"

class Universe {

	public:
		static WindowManager* win_manager;
		static Assets* assets;
		static InputManager* input;
		static MouseManager* mouse;
		static Camera* camera;
		static StateManager* state;
		static Renderer* renderer;
};

Editor::Editor() {
	created = false;
	// 2 x 5 - Minimum Size
	// Above 64 x 64 gets stupid sizes.
	gridwidth = 32;
	gridheight = 32;
	editx = 2;
	edity = 4;
	tileIndex = 2;
	offsetX = 0;
	offsetY = 0;
}

void Editor::create() {

	Tiles::initiate();
	created = true;

	for (int x = 0; x < gridwidth; ++x) {
		vector<Node*> row;
		for (int y = 0; y < gridheight; ++y) {
			Node* node = new Node();
			node->type = Tiles::NONE;
			if (x >= 4 && y == 14 && x <= gridwidth - 4) {
				node->type = Tiles::BLOCK; node->solid = true;
			}
			if ((x >= 5 && y == 15 && x <= gridwidth - 5) ||
				(x >= 6 && y == 16 && x <= gridwidth - 6)) {
				node->type = Tiles::DIRT; node->solid = true;
			}
			row.push_back(node);
		}
		nodes.push_back(row);
	}


	for (int x = 0; x < gridwidth; ++x) {
		vector<Node*> row;
		for (int y = 0; y < gridheight; ++y) {
			Node* editnode = new Node();
			editnode->type = Tiles::NONE;
			row.push_back(editnode);
		}
		editnode.push_back(row);
	}
	src_rect.w = 16; src_rect.h = 16;
	rect.w = 32; rect.h = 32;

	uisrcrect.x = 0; uisrcrect.y = 0;
	uisrcrect.w = 1024; uisrcrect.h = 128;
	uirect.x = 0; uirect.y = universe->win_manager->screen_height - universe->win_manager->screen_height / 6;
	uirect.w = universe->win_manager->screen_width; uirect.h = universe->win_manager->screen_height / 6;

	gridsrcrect.x = 0; gridsrcrect.y = 0;
	gridsrcrect.w = 32; gridsrcrect.h = 32;
	gridrect.x = 0; gridrect.y = 0;
	gridrect.w = 32; gridrect.h = 32;

	selsrcrect.x = 0; selsrcrect.y = 0;
	selsrcrect.w = 32; selsrcrect.h = 32;
	selrect.x = (universe->win_manager->screen_width - universe->win_manager->screen_width / 4 - universe->win_manager->screen_width / 32 - 1) + ((universe->win_manager->screen_width / 31) * tileIndex);
	selrect.y = universe->win_manager->screen_height - universe->win_manager->screen_height / 8;
	selrect.w = universe->win_manager->screen_width / 32; selrect.h = universe->win_manager->screen_height / 24;

	gridwidth = 24;
	gridheight = 16;

	offsetX = (gridwidth * 16) - universe->win_manager->screen_width / 2;
	offsetY = (gridheight * 16) - universe->win_manager->screen_height / 2;
}

void Editor::remove() {
	created = false;
}

void Editor::update() {
	//update and render code here

	//////////// Grid and tiles stuff.

	for (int y = 0; y < gridheight; ++y) {
		for (int x = 0; x < gridwidth; ++x) {
			if (universe->mouse->mouse_pos.x >= (x * 32) - offsetX && universe->mouse->mouse_pos.x < (x * 32) + 32 - offsetX) editx = x;
			if (universe->mouse->mouse_pos.y >= (y * 32) - offsetY && universe->mouse->mouse_pos.y < (y * 32) + 32 - offsetY) edity = y;
			Node* node = nodes[x][y];
			if (node->type != Tiles::NONE) {
				src_rect.x = node->type->src_x; src_rect.y = node->type->src_y;
				rect.x = (x * 32) - offsetX; rect.y = (y * 32) - offsetY;
				universe->renderer->render(universe->assets->tile_sheets[node->type->sheet_index], &src_rect, &rect);
			}
			if (gridEnabled)
			{
				gridrect.x = (x * 32) - offsetX; gridrect.y = (y * 32) - offsetY;
				universe->renderer->render(universe->assets->editgrid, &gridsrcrect, &gridrect);
			}
		}
	}

	Node* node = editnode[editx][edity];
	if (tileIndex == 0) node->type = Tiles::NONE;
	if (tileIndex == 1) node->type = Tiles::BLOCK;
	if (tileIndex == 2) node->type = Tiles::DIRT;

	// CAMERA MOVING 
	if (universe->input->left_key[0]->down && offsetX  > -universe->win_manager->screen_width / 2) {
		offsetX -= 6;
	}
	else if (universe->input->right_key[0]->down && offsetX  < (gridwidth * 32) - universe->win_manager->screen_width / 2) {
		offsetX += 6;
	}
	if (universe->input->up_key[0]->down && offsetY  > -universe->win_manager->screen_height / 2) {
		offsetY -= 6;
	}
	else if (universe->input->down_key[0]->down && offsetY < (gridheight * 32) - universe->win_manager->screen_height / 2) {
		offsetY += 6;
	}

	////////////	Mouse input shit.
	// Map tile placing

	if (universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 6)
	{
		if (universe->mouse->mouse_down) {
			Node* oldnode = nodes[editx][edity];
			oldnode->type = node->type;
		}

		rect.x = (editx * 32) - offsetX; rect.y = (edity * 32) - offsetY;
		src_rect.x = node->type->src_x; src_rect.y = node->type->src_y;
		universe->renderer->render(universe->assets->tile_sheets[node->type->sheet_index], &src_rect, &rect);
	}

	else		// UI interacting Stuff
	{
		if (universe->mouse->mouse_down && !hasClicked) {

			// --------------------------- Selecting tilerinos.
			// First row
			if (universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 12)
			{
				for (int i = 0; i < 8; ++i)
				{
					if (universe->mouse->mouse_pos.x >(universe->win_manager->screen_width - universe->win_manager->screen_width / 4 - universe->win_manager->screen_width / 32) + (universe->win_manager->screen_width / 32 * i)
						&& universe->mouse->mouse_pos.x < (universe->win_manager->screen_width - universe->win_manager->screen_width / 4) + (universe->win_manager->screen_width / 32 * i))
					{
						tileIndex = i;
						selrect.x = (universe->win_manager->screen_width - universe->win_manager->screen_width / 4 - universe->win_manager->screen_width / 32) + ((universe->win_manager->screen_width / 31.9f) * i);
						selrect.y = universe->win_manager->screen_height - universe->win_manager->screen_height / 8;
					}
				}
			}// Second row of buttonserinoatoriama.
			else if (universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 24
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 12 + universe->win_manager->screen_height / 24)
			{
				for (int i = 0; i < 8; ++i)
				{
					if (universe->mouse->mouse_pos.x >(universe->win_manager->screen_width - universe->win_manager->screen_width / 4 - universe->win_manager->screen_width / 32) + (universe->win_manager->screen_width / 32 * i)
						&& universe->mouse->mouse_pos.x < (universe->win_manager->screen_width - universe->win_manager->screen_width / 4) + (universe->win_manager->screen_width / 32 * i))
					{
						tileIndex = i;
						selrect.x = (universe->win_manager->screen_width - universe->win_manager->screen_width / 4 - universe->win_manager->screen_width / 32) + ((universe->win_manager->screen_width / 31.9f) * i);
						selrect.y = universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 24;
					}
				}
			}

			// ---------------- Grid arrow resize shit ---------------- \\

			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width - universe->win_manager->screen_width / 2 + universe->win_manager->screen_width / 8 - universe->win_manager->screen_width / 33
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width - universe->win_manager->screen_width / 2 + universe->win_manager->screen_width / 8 + universe->win_manager->screen_width / 32
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 12 + universe->win_manager->screen_height / 24)
			{
				if (gridEnabled) gridEnabled = false;
				else gridEnabled = true;
				hasClicked = true;
			}

			// ---------------- Grid arrow resize shit ---------------- \\
																								// Grid resize hor +
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 6
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 6 + universe->win_manager->screen_width / 14
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 16
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 10)
			{
				if (gridwidth < 32) ++gridwidth;
				hasClicked = true;
			}// Grid resizw hor -
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 6
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 6 + universe->win_manager->screen_width / 14
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 16
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 10)
			{
				if (gridwidth > 8)  --gridwidth;
				hasClicked = true;
			}// Grid resize vert +
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 32
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 32 + universe->win_manager->screen_width / 14
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 16
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 10)
			{
				if (gridheight < 32) ++gridheight;
				hasClicked = true;
			}// Grid resize vert -
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 30
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width - universe->win_manager->screen_width / 2 - universe->win_manager->screen_width / 30 + universe->win_manager->screen_width / 14
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 16
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 10)
			{
				if (gridheight > 8)  --gridheight;
				hasClicked = true;
			}

			// ---------------- Main buttons shit ---------------- \\

			// Main Menu
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width / 64
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width / 64 + universe->win_manager->screen_width / 8
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 19
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 10)
			{
				universe->state->switch_state(MAIN_MENU);
			}
			// Clear
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width / 32 + universe->win_manager->screen_width / 8
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width / 32 + universe->win_manager->screen_width / 4
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 19
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 - universe->win_manager->screen_height / 14 + universe->win_manager->screen_height / 10)
			{

				for (int y = 0; y < 32; ++y) {
					for (int x = 0; x < 32; ++x) {
						if (universe->mouse->mouse_pos.x >= (x * 32) - offsetX && universe->mouse->mouse_pos.x < (x * 32) + 32 - offsetX) editx = x;
						if (universe->mouse->mouse_pos.y >= (y * 32) - offsetY && universe->mouse->mouse_pos.y < (y * 32) + 32 - offsetY) edity = y;
						Node* node = nodes[x][y];
						if (node->type != Tiles::NONE) {
							node->type = Tiles::NONE;
						}
					}
				}
			}
			// Save
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width / 64
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width / 64 + universe->win_manager->screen_width / 8
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 20
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 10)
			{
				if (gridheight > 8)  --gridheight;
				hasClicked = true;
			}
			// Load
			if (universe->mouse->mouse_pos.x > universe->win_manager->screen_width / 32 + universe->win_manager->screen_width / 8
				&& universe->mouse->mouse_pos.x < universe->win_manager->screen_width / 32 + universe->win_manager->screen_width / 4
				&& universe->mouse->mouse_pos.y > universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 20
				&& universe->mouse->mouse_pos.y < universe->win_manager->screen_height - universe->win_manager->screen_height / 8 + universe->win_manager->screen_height / 10)
			{
				if (gridheight > 8)  ++gridheight;
				hasClicked = true;
			}
		}
		else
		{
			if (!universe->mouse->mouse_down) hasClicked = false;
		}
	}

	uirect.x = 0; uirect.y = universe->win_manager->screen_height - universe->win_manager->screen_height / 6;
	uirect.w = universe->win_manager->screen_width; uirect.h = universe->win_manager->screen_height / 6;
	selrect.w = universe->win_manager->screen_width / 32; selrect.h = universe->win_manager->screen_height / 24;


	universe->renderer->render(universe->assets->editorUI, &uisrcrect, &uirect);
	universe->renderer->render(universe->assets->selecty, &selsrcrect, &selrect);
}