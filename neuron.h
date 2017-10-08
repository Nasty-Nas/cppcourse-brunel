#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron {
	
private :
	double V_; //membrane potential (mV)
	int nb_spikes_;
	std::vector<double> spike_times_;
	double threshold_; //potential for which the neuron spikes (mV)
	double tau_; //period where neuron is refractory (seconds)
	double time_;
	bool is_refractory_; //ture = neuron is in refractory period
	double ref_period_; //value going form [0 to tau_], when == to tau_ -> end of refractory period

public :
	
	//Constructor
	Neuron(double t);
	
	//getters and setters
	double getV();
	int getNb_spikes();
	std::vector<double> getSpike_times();
	double getTime();
	void setV(double);
	void setNb_spikes(int);
	void setTime (double);
	
	//update method
	void update(double);
};

#endif