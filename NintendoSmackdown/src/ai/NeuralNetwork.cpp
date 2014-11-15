#include "NeuralNetwork.h"
#include <iostream>
#include <Windows.h>

class Universe {

	public:
};

NeuralNetwork::NeuralNetwork() {
	hiddenlayers = 0;
	startinputs = 8;
	hiddenneurons = 24;
	outputneurons = 4;
}

void NeuralNetwork::create() {
	layers.push_back(NeuronLayer(hiddenneurons, startinputs));
	for (int n = 0; n < hiddenlayers; ++n) {
		layers.push_back(NeuronLayer(hiddenneurons, layers[layers.size() - 1].neuronlen));
	}
	layers.push_back(NeuronLayer(outputneurons, layers[layers.size() - 1].neuronlen));

	cout << "created neural network\n";
}

double sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

vector<double> NeuralNetwork::update(vector<double> inputs) {
	vector<double> outputs;

	for (int i = 0; i < layers.size(); ++i) {
		if (i > 0) { inputs = outputs; }
		outputs.clear();
		for (int n = 0; n < layers[i].neuronlen; ++n) {
			double weightsum = 0;
			for (int p = 0; p < layers[i].neurons[n].inputlen - 1; ++p) {
				weightsum += layers[i].neurons[n].weights[p] * inputs[p];
			}
			weightsum += layers[i].neurons[n].weights[layers[i].neurons[n].inputlen - 1] * -1;

			double result = sigmoid(weightsum);
			if (isnan(result)) { outputs.push_back(0); }else { outputs.push_back(result); }
		}
	}

	return outputs;
}

void NeuralNetwork::setweights(vector<double> genome) {
	int weightindex = 0;
	for (int i = 0; i < layers.size(); ++i) {
		for (int n = 0; n < layers[i].neuronlen; ++n) {
			for (int p = 0; p < layers[i].neurons[n].inputlen; ++p) {
				layers[i].neurons[n].weights[p] = genome[weightindex];
				++weightindex;
			}
		}
	}
}

int NeuralNetwork::getweights() {
	int weight = 0;
	for (int i = 0; i < layers.size(); ++i) {
		for (int n = 0; n < layers[i].neuronlen; ++n) {
			for (int p = 0; p < layers[i].neurons[n].inputlen; ++p) {
				++weight;
			}
		}
	}
	return weight;
}