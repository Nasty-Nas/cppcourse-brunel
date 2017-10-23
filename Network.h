#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
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

private:
	//all neurons in the network
	std::vector<Neuron> neurons_;

	//all connections in the network
	//integers in vector(i) indicate which nerons are conntected to neuron(i)
	std::vector<std::vector<int> > connections_;

	const int transmission_delay_ = (15); //delay after which spike is transmitted (in steps)

};

#endif