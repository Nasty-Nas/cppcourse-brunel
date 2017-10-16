#include <iostream>
#include <cmath>
#include "neuron.h"

//Constructor
Neuron::Neuron(double t)
	:clock_(t), isRefractory_(false), V_(-70), ref_period_(0), nb_spikes_(0)
{}

//Setters and Getters
double Neuron::getV() {
	return V_;
}

int Neuron::getNb_spikes() {
	return nb_spikes_;
}

std::vector<double> Neuron::getSpike_times() {
	return spike_times_;
}

double Neuron::getTime() {
	return clock_;
}

void Neuron::setTime(double t) {
	clock_ = t;
}

//update method
bool Neuron::update(double I) {
	bool spiked = false;
	if (isRefractory_ == true) {
		V_ = 0;
		ref_period_ += h_;
		if (ref_period_ >= t_ref_)
		{
			isRefractory_ = false;
			ref_period_ = 0;
			V_ = 10;
		}
		
	} else if (V_ >= threshold_) {
		spike_times_.push_back(clock_);
		nb_spikes_ +=1;
		spiked = true;
		V_ = 0;
		isRefractory_ = true;
	} else {
		V_ = (((exp(-h_/tau_))*V_) + (I*R_*(1-(exp(-h_/tau_)))));
	}
	clock_ ++;
	return spiked;
}