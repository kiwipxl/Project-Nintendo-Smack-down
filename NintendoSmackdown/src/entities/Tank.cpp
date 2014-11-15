#include "Tank.h"
#include <iostream>
#include "../managers/WindowManager.h"
#include "../map/Map.h"
#include "../managers/Assets.h"
#include "../ui/UIManager.h"
#include "Item.h"
#include <Windows.h>
#include "EntityManager.h"

class Universe {

	public:
		static WindowManager* winmanager;
		static Map* map;
		static Assets* assets;
		static UIManager* uimanager;
		static EntityManager* entitymanager;
};

Tank::Tank(int x, int y) {
	pos.x = x; pos.y = y;
	brain = NeuralNetwork();
	brain.create();
	rect.x = 0; rect.y = 0; rect.w = 32; rect.h = 32;
	origin.x = rect.w / 2; origin.y = rect.h / 2;
	cannonorigin.x = rect.w / 2; cannonorigin.y = rect.h / 2;
	rotation = 0;
	cannonrotation = 0;
	fitness = 0;
	firetimer = 0;
	firerate = 80 + (rand() % 40);
}

void Tank::update() {
	vector<double> inputs;

	if (universe->entitymanager->items.size() >= 1) {
		float closestdist = INT_MAX;
		Item* closestitem = NULL;

		for (Item* item : universe->entitymanager->items) {
			float dist = sqrt(pow(item->pos.x - pos.x, 2) + pow(item->pos.y - pos.y, 2));
			if (dist < closestdist) {
				closestdist = dist;
				closestitem = item;
			}

			if (dist <= 24) {
				++fitness;
				item->setrandompos();
			}
		}
		
		closestdist = INT_MAX;
		Tank* closesttank = NULL;

		for (Tank* tank : universe->entitymanager->tanks) {
			if (tank != this) {
				float dist = sqrt(pow(tank->pos.x - pos.x, 2) + pow(tank->pos.y - pos.y, 2));
				if (dist < closestdist) {
					closestdist = dist;
					closesttank = tank;
				}
			}
		}

		for (Bullet* bullet : universe->entitymanager->bullets) {
			if (bullet->tank != this) {
				if (sqrt(pow(bullet->pos.x - pos.x, 2) + pow(bullet->pos.y - pos.y, 2)) <= 24) {
					bullet->removed = true;
					if (bullet->closesttank == this) {
						++fitness;
					}
				}
			}
		}

		double closex = pos.x - closestitem->pos.x;
		double closey = pos.y - closestitem->pos.y;
		inputs.push_back(closex / sqrt((closex * closex) + (closey * closey)));
		inputs.push_back(closey / sqrt((closex * closex) + (closey * closey)));
		inputs.push_back(lookat.x);
		inputs.push_back(lookat.y);
		closex = pos.x - closesttank->pos.x;
		closey = pos.y - closesttank->pos.y;
		inputs.push_back(closex / sqrt((closex * closex) + (closey * closey)));
		inputs.push_back(closey / sqrt((closex * closex) + (closey * closey)));
		inputs.push_back(cannonlookat.x);
		inputs.push_back(cannonlookat.y);
		/**
		if (pos.x >= universe->winmanager->centerx) {
			closex = (universe->winmanager->screenwidth - pos.x) / universe->winmanager->screenwidth;
		}else { closex = pos.x / universe->winmanager->centerx; }
		if (pos.y >= universe->winmanager->centery) {
			closey = (universe->winmanager->screenheight - pos.y) / universe->winmanager->screenheight;
		}else { closey = pos.y / universe->winmanager->centery; }
		inputs.push_back(closex);
		inputs.push_back(closey);
		**/

		vector<double> outputs = brain.update(inputs);

		double ltrack = outputs[0];
		double rtrack = outputs[1];
		double lcannon = outputs[2];
		double rcannon = outputs[3];

		double speed = ltrack + rtrack;
		float maxspeed = 2;
		if (speed < -maxspeed) { speed = -maxspeed; }else if (speed > maxspeed) { speed = maxspeed; }

		float turnspeed = .1f;
		double turnforce = ltrack - rtrack;
		if (turnforce < -turnspeed) { turnforce = -turnspeed; }else if (turnforce > turnspeed) { turnforce = turnspeed; }
		rotation += turnforce;

		lookat.x = cos(rotation);
		lookat.y = -sin(rotation);
		pos.x += lookat.x * speed;
		pos.y += lookat.y * speed;

		turnspeed = .1f;
		turnforce = lcannon - rcannon;
		if (turnforce < -turnspeed) { turnforce = -turnspeed; }else if (turnforce > turnspeed) { turnforce = turnspeed; }
		cannonrotation += turnforce;
		cannonlookat.x = cos(cannonrotation + rotation);
		cannonlookat.y = -sin(cannonrotation + rotation);

		++firetimer;
		if (firetimer >= firerate) {
			Bullet* bullet = EntityManager::createbullet(pos.x + origin.x, pos.y + origin.y, cannonrotation + rotation);
			bullet->tank = this;
			bullet->closesttank = closesttank;
			firetimer = 0;
		}

		//if (pos.x < 0) { pos.x = 0;
		//}else if (pos.x > universe->winmanager->screenwidth - 32) { pos.x = universe->winmanager->screenwidth - 32; }
		//if (pos.y < 0) { pos.y = 0;
		//}else if (pos.y > universe->winmanager->screenheight - 32) { pos.y = universe->winmanager->screenheight - 32; }

		if (pos.x < 0) { pos.x = universe->winmanager->screenwidth - 32;
		}else if (pos.x > universe->winmanager->screenwidth - 32) { pos.x = 0; }
		if (pos.y < 0) { pos.y = universe->winmanager->screenheight - 32;
		}else if (pos.y > universe->winmanager->screenheight - 32) { pos.y = 0; }

		rect.x = pos.x; rect.y = pos.y;
	}
}

void Tank::render() {
	SDL_RenderCopyEx(universe->winmanager->renderer, universe->assets->tank, NULL, &rect,
		-rotation / (M_PI / 180), &origin, SDL_RendererFlip::SDL_FLIP_NONE);
	SDL_RenderCopyEx(universe->winmanager->renderer, universe->assets->tankcannon, NULL, &rect,
		-(cannonrotation + rotation) / (M_PI / 180), &cannonorigin, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Tank::reset() {
	fitness = 0;
	rotation = 0;
	pos.x = 32 + (rand() % (universe->winmanager->screenwidth - 32));
	pos.y = 32 + (rand() % (universe->winmanager->screenheight - 32));
}