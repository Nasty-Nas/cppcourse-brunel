#include <cassert>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include "Neuron.h"
#include "Network.h"


Neuron::Neuron(bool type)
	:
	potential_(0.0),
	nb_spikes_(0),
	clock_(0),
	isRefractory_(false),
	ref_period_(0),
	spike_buff_(),
	i_ext_(0.0),
	isExcitatory_(type)
{
	spike_buff_.resize(transmission_delay_ +1, 0.0);
	assert(spike_buff_.size()== (size_t) transmission_delay_+1);
	c1_ = exp(-step_duration_/tau_);
	c2_ = R_ * (1.0 - c1_);

}

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

bool Neuron::isExcitatory() const {
	return isExcitatory_;
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
	if (isExcitatory_)
	{
		return J_excitatory_;
	}else{
		return J_inhibitory_;
	}
}

void Neuron::recieve_spike(double j, int arrival) {
	spike_buff_[arrival % spike_buff_.size()] += j;
}

double Neuron::get_background_noise() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::poisson_distribution<> poisson(2);
	return poisson(gen);
}

bool Neuron::update() {
	bool spiked = false;
	if (isRefractory_) {
		potential_ = 0.0;
		ref_period_ ++;
		if (ref_period_ >= (t_ref_ - 1))
		{
			isRefractory_ = false;
			ref_period_ = 0;
		}	
	} else if (potential_ >= threshold_) {
		spike_times_.push_back(clock_);
		nb_spikes_ ++;
		spiked = true;
		isRefractory_ = true;
		potential_ = 0.0;
	} else {
		potential_ = ((c1_*potential_) + (i_ext_*c2_));
		potential_ += spike_buff_[clock_ % spike_buff_.size()];
		potential_ += get_background_noise();
	}
	//reset buffer potential for this time step (after it was added to the neuron's potential)
	spike_buff_[clock_ % spike_buff_.size()] = 0.0;
	clock_ ++;
	return spiked;
}

bool Neuron::update_no_noise() {
	bool spiked = false;
	if (isRefractory_) {
		potential_ = 0.0;
		ref_period_ ++;
		if (ref_period_ >= (t_ref_ - 1))
		{
			isRefractory_ = false;
			ref_period_ = 0;
		}	
	} else if (potential_ >= threshold_) {
		spike_times_.push_back(clock_);
		nb_spikes_ ++;
		spiked = true;
		isRefractory_ = true;
		potential_ = 0.0;
	} else {
		potential_ = ((c1_*potential_) + (i_ext_*c2_));
		potential_ += spike_buff_[clock_ % spike_buff_.size()];
		//potential_ += get_background_noise();
	}
	//reset buffer potential for this time step (after it was added to the neuron's potential)
	spike_buff_[clock_ % spike_buff_.size()] = 0.0;
	clock_ ++;
	return spiked;
}