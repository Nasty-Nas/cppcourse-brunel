#include <cassert>
#include <iostream>
#include <cmath>
#include "Neuron.h"

//Constructor
Neuron::Neuron(bool type)
	:
	potential_(0.0),
	nb_spikes_(0),
	clock_(0),
	isRefractory_(false),
	ref_period_(0),
	spike_buff_(),
	i_ext_(0.0)
	isExcitatory(type);
{
	spike_buff_.resize(transmission_delay_ +1, 0.0);
	assert(spike_buff_.size()==transmission_delay_+1);
	c1_ = exp(-step_duration_/tau_);
	c2_ = R_ * (1.0 - c1_);

}

//Setters and Getters
double Neuron::getPotential() const {
	return potential_;
}

int Neuron::getNb_spikes() const {
	return nb_spikes_;
}

std::vector<double> Neuron::getSpike_times() const {
	return spike_times_;
}

int Neuron::getTime() const {
	return clock_;
}

/**
 * get if neuron is exitatory or inhibitory
 * @return true = exitatory, false =inhibitory
 */
bool Neuron::isExcitatory() const {
	return isExcitatory_;
}

void Neuron::setTime(int t) {
	clock_ = t;
}

void Neuron::set_i_ext(double i) {
	i_ext_ = i;
}

std::vector<int> Neuron::getTarget_co() const {
	return target_co_;
}

void Neuron::setTarget_co(int i) {
	target_co_.push_back(i);
}

double Neuron::getJ() const {
	if (isExcitatory)
	{
		return J_excitatory_;
	}else{
		return J_inhibitory_;
	}
}

/**
 * stores incoming spikes in buffer
 * @param j [weight of post synaptic potential]
 * @param arrival [time at which the spike arrives]
 */
void Neuron::recieve_spike(double j, int arrival) {
	spike_buff_[arrival % spike_buff_.size()] += j;
}

/**
 * Updates a neuron's membrane potential for each time step and checks for spike condition
 * @return bool (true if the neuron spiked at this time step)
 */
bool Neuron::update() {
	bool spiked = false;
	if (isRefractory_) {
		potential_ = 0.0;
		ref_period_ ++;
		if (ref_period_ >= t_ref_)
		{
			isRefractory_ = false;
			ref_period_ = 0;
		}	
	} else if (potential_ >= threshold_) {
		spike_times_.push_back(clock_);
		nb_spikes_ ++;
		spiked = true;
		isRefractory_ = true;
	} else {
		potential_ = ((c1_*potential_) + (i_ext_*c2_));
		potential_ += spike_buff_[clock_ % spike_buff_.size()];
		potential_ += Network::get_background_noise();
	}
	//reset buffer potential for this time step (after it was added to the neuron's potential)
	spike_buff_[clock_ % spike_buff_.size()] = 0.0;
	clock_ ++;
	return spiked;
}