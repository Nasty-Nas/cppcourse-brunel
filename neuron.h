#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron {
	
private :
	double V_; //membrane potential (mV)
	int nb_spikes_;
	std::vector<int> spike_times_;
	double threshold_; //potential for which the neuron spikes (mV)
	double tau_; //period where neuron is refractory (seconds)
	int time_;
	double ref_;

public :
	
	//Constructor
	Neuron(int t);
	
	//getters and setters
	double getV();
	int getNb_spikes();
	std::vector<int> getSpike_times();
	int getTime();
	void setV(double);
	void setNb_spikes(int);
	void setTime (int);
	
	//update method
	void update(double);
};

#endif