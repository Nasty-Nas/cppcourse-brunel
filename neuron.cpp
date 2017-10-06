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

int Neuron::getTime const() {
	return time_;
}

void Neuron::setTime(int t) {
	time_ = t;
}

//update method
void Neuron::update() {

}
