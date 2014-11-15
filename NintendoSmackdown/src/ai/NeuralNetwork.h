#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <SDL.h>
#include "../tools/Universal.h"
#include "Genetics.h"

class Neuron {

	public:
		Neuron(int newinputlen) {
			inputlen = newinputlen + 1;
			for (int i = 0; i < inputlen; ++i) {
				weights.push_back(0);
			}
		}

		int inputlen;
		vector<double> weights;
};

class NeuronLayer {

	public:
		NeuronLayer(int newneuronlen, int inputsperneuron) {
			neuronlen = newneuronlen;
			for (int i = 0; i < neuronlen; ++i) {
				neurons.push_back(Neuron(inputsperneuron));
			}
		}

		int neuronlen;
		vector<Neuron> neurons;
};

class NeuralNetwork : Universal {

	public:
		NeuralNetwork();

		void create();
		vector<double> update(vector<double> inputs);

		void setweights(vector<double> genome);
		int getweights();

	private:
		int hiddenlayers;
		int startinputs;
		int hiddenneurons;
		int outputneurons;
		vector<NeuronLayer> layers;
};

#endif