#include <iostream>
#include "Network.h"

Network::Network() {
	//create 2 neurons
	Neuron n0, n1;
	//add these two neurons to our network
	neurons_ = std::vector<Neuron>();
	neurons_.push_back(n0);
	neurons_.push_back(n1);
	
	//add a connection between n0 and n1
	connections_ = { { 1 }, { 0 } };

}

Network::~Network() {}


/**
 * Sets external current i for neuron n
 * @param n [neuron number]
 * @param i [external current]
 */
void Network::set_current(int n, double i){
	neurons_.at(n-1).set_i_ext(i);
}

double Network::get_potential(int n){
	double v = neurons_.at(n-1).getPotential();
	return v;
}

/**
 * Updates all neurons in the network
 * If a neruon spikes, it sends spike to all connected neurons
 * @param  t [simulation global time]
 * @return        [description]
 */
void Network::update(int t) {
	for (size_t i = 0; i < neurons_.size(); ++i)
	{

		bool spiked = neurons_.at(i).update();

		if (spiked)
		{
			std::cout << "Spike from neuron" << i << " at t = " << t*0.1 << "ms\n";
			//for each neuron (target) connected to neuron(i) : transmit a spike with a delay
			for (auto target : connections_.at(i))
			{
				neurons_.at(target).recieve_spike(0.1, t + transmission_delay_);
			}
		}
	}
}