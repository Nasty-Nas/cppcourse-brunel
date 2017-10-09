#include <iostream>
#include <cmath>
#include "neuron.h"

//Constructor
Neuron::Neuron(double t)
	:time_(t), is_refractory_(false), V_(-70), ref_period_(0), nb_spikes_(0)
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
	if (is_refractory_ == true) {
		V_ = 0;
		ref_period_ += h_;
		if (ref_period_ >= t_ref_)
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
		V_ = (((exp(-h_/tau_))*V_) + (I*R_*(1-(exp(-h_/tau_)))));
	}
	time_ += h_;	
}