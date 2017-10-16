#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron {
	
private :
	double V_; //membrane potential (mV)
	int nb_spikes_;
	std::vector<double> spike_times_;
	const double threshold_ = 20; //potential for which the neuron spikes (mV)
	const double tau_ = (200); //membrane time constant(time steps)
	const double R_ = (200);
	const int h_ = (1); //0.1 ms
	const double t_ref_ = (20); //period where neuron is refractory in time steps(20*h_) =2ms
	double clock_;
	bool isRefractory_; //true = neuron is in refractory period
	double ref_period_; //value going form [0 to t_ref_], when == to t_ref_ -> end of refractory period

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
	bool update(double);
};

#endif