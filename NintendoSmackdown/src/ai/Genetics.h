#ifndef GENETICS_H
#define GENETICS_H

#include <SDL.h>
#include <ctime>
#include <algorithm>
#include <map>
#include <vector>
#include <sstream>
#include <math.h>
#include "../tools/Universal.h"
#include "../tools/Point2D.h"

using namespace std;

#define RANDMAXF (float)(RAND_MAX + 1)

class Chromosome {

	public:
		vector<double> genome;
		float fitness;

		Chromosome() {
			fitness = 0;
		}

		Chromosome(vector<double> newgenome) {
			genome = newgenome;
			fitness = 0;
		}
};

class Genetics : Universal {

	public:
		Genetics(int newgenelength, int newpopsize);

		vector<Chromosome> population;
		
		vector<Chromosome> epoch(vector<Chromosome>& prevpopulation);

	private:
		int genelength;
		int popsize;

		Chromosome roulette(float total);
		void mutate(vector<double>& a);
		void crossover(vector<double>& a, vector<double>& b);
};

#endif