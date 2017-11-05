#include <iostream>
#include "Network.h"

#include <random>
#include <algorithm>
#include <fstream>


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
		neurons_.push_back(Neuron(excitatory));
	}

	//generate random connections for each neuron
	for (int i = 0; i < n_total_; ++i)
	{
		create_connexions(i);
	}
	
}

Network::~Network() {}


void Network::set_current(int n, double i){
	neurons_[n-1].set_i_ext(i);
}

double Network::get_potential(int n){
	double v = neurons_[n-1].getPotential();
	return v;
}

void Network::update(int t) {
	std::ofstream outFile;
	outFile.open("spikes.gdf");

	for (int s = 0; s < t; ++s)
	{
	
		for (size_t i = 0; i < neurons_.size(); ++i)
		{

			bool spiked = neurons_[i].update();

			if (spiked)
			{
				outFile << neurons_[i].getTime() << '\t' << i << '\n';
				//for each neuron (target) connected to neuron(i) : transmit a spike with a delay
				for (auto target : neurons_[i].getTarget_co())
				{
					neurons_[target].recieve_spike(neurons_[i].getJ(), s + transmission_delay_);
				}
			}
		}
	}

	outFile.close();
}

