#include <iostream>
#include <cmath>
#include "neuron.h"

//Constructor
Neuron::Neuron(double t)
	:threshold_(20), tau_(0.002), time_(t), is_refractory_(false), V_(-70), ref_period_(0)
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
	return time_;
}

void Neuron::setTime(double t) {
	time_ = t;
}

//update method
void Neuron::update(double I) {
	double h = 0.001;
	if (is_refractory_ == true) {
		V_ = 0;
		ref_period_ += h;
		if (ref_period_ == tau_)
		{
			is_refractory_ = false;
			ref_period_ = 0;
			V_ = 10;
		}
		
	} else if (V_ >= threshold_) {
		spike_times_.push_back(time_);
		nb_spikes_ +=1;
		V_ = 0;
		is_refractory_ = true;
	} else {
		double R = tau_;
		V_ = (((exp(-h/tau_))*V_) + (I*R*(1-(exp(-h/tau_)))));
	}
	time_ += h;	
}