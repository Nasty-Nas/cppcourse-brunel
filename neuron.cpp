#include <iostream>
#include "neuron.h"
#include <cmaths>

using namespace std;

//Constructor

Neuron::Neuron(int t) {
	time_ = t;
}

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

void Neuron::update(double Iext) {
		
	if (ref_ = 0) {
		V_ = 10;
		ref -= 1;
			
	} else {
			
		V_ = ((eps(-h/tau_)*V_) + (Iext*R*(1-eps(-h/tau))))
	}
		
	if (V_ >= threshold_) {
			
		spike_times_.pushback(time_);
		ref = tau_/h;
		nb_spikes_ +=1;
			
	}
	time_ += h;
}
