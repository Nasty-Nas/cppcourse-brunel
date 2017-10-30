#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <array>
#include "Neuron.h"

class Network {
public:
	//Constructor
	Network();
	//Destructor
	virtual ~Network();
	//update neurons in network
	void update(int t);

	void set_current(int n, double i);
	double get_potential(int n);
	double get_background_noise();

	void create_connections();

private:

	const int n_excitatory_ = (10000); //number of excitatory neurons
	const int n_inhibitory_ = (2500); //number of inhibitory neurons
	const int n_total_ = (12500); //total number of neurons
	const int c_excitatory_ = (1000); //number of incoming excitatory connections to a neuron
	const int c_inhibitory_ = (250); //number of incoming inhibitory connections to a neuron
	const int c_total_ = (1250); //number of total incoming connections to a neuron
	const double v_ext_ = (threshold_ / (c_excitatory_ * (J_excitatory_ * tau_ * 0.001); // frequency of external input (0.001 to get tau in seconds)
	const int transmission_delay_ = (15); //delay after which spike is transmitted (in steps)

	std::array<Neuron, n_total_> neurons_; //all neurons in the network



};

#endif