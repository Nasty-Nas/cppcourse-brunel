#include <iostream>
#include "Network.h"

#include <random>
#include <algorithm>

Network::Network() {
	//generate neurons in our network
	for (int i = 0; i < n_total_; ++i)
	{
		bool excitatory = false;
		//the first 10000 neurons are excitatroy, the rest are inhibitory
		if (i < n_excitatory_)
		{
			excitatory = true;
		}
		neurons_[i] = Neuron(excitatory);
	}

	//generate random connections
	std::array<int, c_excitatory_> excitatory_array; //array that will be filled with indexes of excitatory neurons to connect to a target neuron
	std::array<int, c_inhibitory_> inhibitory_array; //array that will be filled with indexes of inhibitory neurons to connect to a target neuron

	//for each neuron, create c_excitatory_ excitatory connections
	//and c_inhibitory_ inhibitory connections
	for (int i = 0; i < n_total_; ++i)
	{
		create_connexions(0, n_excitatory_ - 1, excitatory_array, i); //randomly picks excitatory neurons to connect to i
		create_connexions(n_excitatory_, n_inhibitory_ - 1, inhibitory_array, i); //randomly picks inhibitory neurons to connect to i
	}
	
}

Network::~Network() {}


/**
 * Sets external current i for neuron n
 * @param n neuron number
 * @param i external current
 */
void Network::set_current(int n, double i){
	neurons_.at(n-1).set_i_ext(i);
}

double Network::get_potential(int n){
	double v = neurons_.at(n-1).getPotential();
	return v;
}

/**
 * Generates random background noise
 * using a poison ditribution
 * @return background noise (double)
 */
double Network::get_background_noise() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::poisson_distribution<> poisson(v_ext_ * c_excitatory_ * step_duration_ * J_excitatory_);
	return poisson(gen);
}

template<std::size_t size>
/**
 * indicates random neurons to connect to a target neuron
 * @param min smallest number we can generate (smallest index of random neuron possible)
 * @param max biggest number we can generate (biggest index of random neuron possible)
 * @param a   array that determines how many random numbers we generate (how many neurons we connect to n)
 * @param n   target neuron we are connecting the random neurons to
 */
void create_connexions(int min, int max, std::array<int, size> a, int n) {
	std::default_random_engine engine;
	std::uniform_int_distribution<int> unid(min,max);
	
	//fill array with the random numbers (indexes of neurons connected to target neuron n)
	std::generate(a.begin(), a.end(), unid(engine));

	//for each random neuron we picked, connect it to n (set n as one of its targets)
	for (int i = 0; i < a.size(); ++i)
	{
		neurons_[a[i]].setTarget_co(n);
	}
}

/**
 * Updates all neurons in the network
 * If a neruon spikes, it sends spike to all connected neurons
 * @param  t simulation global time
 */
void Network::update(int t) {
	for (size_t i = 0; i < neurons_.size(); ++i)
	{

		bool spiked = neurons_.at(i).update();

		if (spiked)
		{
			std::cout << "Spike from neuron " << i << " at t = " << t*0.1 << "ms\n";
			//for each neuron (target) connected to neuron(i) : transmit a spike with a delay
			for (auto target : neurons_.at(i).getTarget_co())
			{
				neurons_.at(target).recieve_spike(neurons_.at(i).getJ(), t + transmission_delay_);
			}
		}
	}
}