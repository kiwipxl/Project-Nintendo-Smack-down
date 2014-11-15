#include "Genetics.h"
#include <iostream>
#include "../ui/UIManager.h"

class Universe {

	public:
		static UIManager* uimanager;
};

Genetics::Genetics(int newgenelength, int newpopsize) {
	genelength = newgenelength;
	popsize = newpopsize;

	cout << "genelength: " << genelength << "\n";

	for (int i = 0; i < popsize; ++i) {
		Chromosome chromo = Chromosome();
		for (int n = 0; n < genelength; ++n) {
			chromo.genome.push_back((rand() / RANDMAXF) - (rand() / RANDMAXF));
		}
		population.push_back(chromo);
	}
}

Chromosome Genetics::roulette(float total) {
	float spin = total * (rand() / RANDMAXF);
	float currfitness = 0;
	for (int n = 0; n < popsize + 1; ++n) {
		currfitness += population[n].fitness;
		if (currfitness >= spin) {
			return population[n];
		}
	}
}

void Genetics::mutate(vector<double>& a) {
	for (int n = 0; n < genelength; ++n) {
		if (rand() / RANDMAXF <= .001f) {
			a[n] += ((rand() / RANDMAXF) - (rand() / RANDMAXF)) * .4f;
			//if (a[n] < -1) { a[n] = -1; }else if (a[n] > 1) { a[n] = 1; }
		}
	}
}

void Genetics::crossover(vector<double>& a, vector<double>& b) {
	if (a != b && rand() % 100 <= 70) {
		int startindex = rand() % genelength;
		double temp;
		for (int i = startindex; i < genelength; ++i) {
			temp = a[i];
			a[i] = b[i];
			b[i] = temp;
		}
	}
}

vector<Chromosome> Genetics::epoch(vector<Chromosome>& prevpopulation) {
	srand(time(NULL));

	population = prevpopulation;
	prevpopulation.clear();

	sort(begin(population), end(population), [](Chromosome a, Chromosome b) ->bool { return a.fitness < b.fitness; });

	double totalfitness = 0;
	for (Chromosome chromo : population) {
		totalfitness += chromo.fitness;
	}

	++universe->uimanager->generation;
	universe->uimanager->updateinfotext(population[0].fitness, population[popsize - 1].fitness, 
		(totalfitness / (float)population.size()), totalfitness);

	vector<Chromosome> newpopulation;

	for (int i = 0; i < 4; ++i) {
		newpopulation.push_back(population[popsize - 1 - i]);
	}

	while (newpopulation.size() < popsize) {
		Chromosome newa = Chromosome(roulette(totalfitness).genome);
		Chromosome newb = Chromosome(roulette(totalfitness).genome);

		crossover(newa.genome, newb.genome);
		mutate(newa.genome);
		mutate(newb.genome);

		newpopulation.push_back(newa);
		newpopulation.push_back(newb);
	}

	population.clear();
	cout << "new population created of size: " << newpopulation.size() << "\n";
	cout << "popsize: " << popsize << "\n";

	return newpopulation;
}