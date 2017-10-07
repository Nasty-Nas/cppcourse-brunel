#include <iostream>
#include <cmaths>
#include "neuron.h"

using namespace std;

//Constructor
Neruon::Neruon(int t)
	:threshold_(20), tau_(0.002), time_(t)
{}

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
void Neuron::update(double I) {
		
	if (ref_ = 0) {
		V_ = 10;
		ref -= 1;
			
	} else {
			
		V_ = ((eps(-h/tau_)*V_) + (I*R*(1-eps(-h/tau_))))
	}
		
	if (V_ >= threshold_) {
		
		spike_times_.pushback(time_);
		ref = tau_/h;
		nb_spikes_ +=1;	
	}
	time_ += h;
}
