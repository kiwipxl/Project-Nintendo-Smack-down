#ifndef TANK_H
#define TANK_H

#include <SDL.h>
#include <vector>
#include "../tools/Universal.h"
#include "../tools/Point2DF.h"
#include "../ai/NeuralNetwork.h"

class EntityManager;

class Tank : Universal {

	public:
		Tank(int x, int y);

		int fitness;

		void update();
		void render();
		void reset();

		void setweights(vector<double> genome) { brain.setweights(genome); }
		int getweights() { return brain.getweights(); }

	private:
		NeuralNetwork brain;

		Point2DF pos;
		SDL_Rect rect;

		SDL_Point origin;
		double rotation;
		Point2DF lookat;

		SDL_Point cannonorigin;
		double cannonrotation;
		Point2DF cannonlookat;

		int firetimer;
		double firerate;
};

#endif