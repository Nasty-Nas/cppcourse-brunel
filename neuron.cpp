#include <iostream>
#include "neuron.h"


//Setters and Getters
double Neuron::getV const() {
	return V_;
}

int Neuron::getNb_spikes const() {
	return nb_spikes_;
}

vector<int> Neuron::getSpike_times const() {
	return spike_times_;
}

void Neuron::update() 
