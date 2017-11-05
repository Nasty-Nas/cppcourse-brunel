#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <array>
#include "Neuron.h"
#include <random>
#include <algorithm>

/**
 * Represents a network of neurons in the brain.
 * The network contains 12500 neurons : 10000 of them are excitatory, 2500 are inhibitory.
 * These neurons are randomly connected and send signals to each other
 *
 * @author Seddiki Anas
 */
class Network {

public:
	/**
	 * Network constructor that generates the neurons and connects them randomly together
	 */
	Network();
	
	/// Destructor
	virtual ~Network();

	/**
	 * Sets external current i for neuron n
	 * @param n neuron number
	 * @param i external current
	 */
	void set_current(int n, double i);

	/**
	 * Get the membrane potential of a given neuron in out network
	 * @param  n index of the neuron of interest (in neurons_)
	 * @return   the membrane potential of the neuron of interest
	 */
	double get_potential(int n);
	
	/**
	 * Randomly chooses 1000 excitatory and 250 inhibitory neurons in our network
	 * and connects them to a given target neuron
	 * @param n target neuron we want to generate connexions for
	 */
	void create_connexions(int n) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> exct(0,9999);
		std::uniform_int_distribution<> inhib(10000,12499);

		for (int i = 0; i < c_excitatory_; ++i)
		{
			auto source= exct(gen);
			neurons_[source].setTarget_co(n);

		}
		for (int i = 0; i < c_inhibitory_; ++i)
		{
			auto source= inhib(gen);
			neurons_[source].setTarget_co(n);

		}
	}

	/**
	 * Updates all the neurons in our network over a given number of time steps
	 * If a neuron in our network spikes, its spike time is recorded in an external file:
	 * "spikes.gdf" found in the build directory
	 * @param t number of time steps we update our network over
	 * @see Neuron::update()
	 */
	void update(int t);

private:

	const int n_excitatory_ = 10000; //!< number of excitatory neurons in the network
	const int n_inhibitory_ = 2500; //!< number of inhibitory neurons in the network
	const static int n_total_ = 12500; //!< total number of neurons in the network
	const int c_excitatory_ = 1000; //!< number of incoming excitatory connections to a neuron
	const int c_inhibitory_ = 250; //!< number of incoming inhibitory connections to a neuron
	const int c_total_ = 1250; //!< number of total incoming connections to a neuron
	const int transmission_delay_ = 15; //!< delay after which spike is transmitted (in steps)

	std::vector<Neuron> neurons_; //!< all neurons in the network



};

#endif