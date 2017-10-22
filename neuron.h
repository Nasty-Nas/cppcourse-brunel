#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

class Neuron {
	
private :
	double potential_; //membrane potential (mV)
	int nb_spikes_;
	std::vector<double> spike_times_;
	int clock_; //internal time of neuron in steps
	bool isRefractory_; //true = neuron is in refractory period
	int ref_period_; //value going form [0 to t_ref_], when == to t_ref_ -> end of refractory period
	std::vector<double> spike_buff_;
	double i_ext_; //external current

	//////////////
	//constants //
	//////////////
	const double threshold_ = 20.0; //potential for which the neuron spikes (mV)
	const double tau_ = (20.0); //membrane time constant(time steps)
	const double R_ = (20.0); //Memebrane resistance
	const int h_ = (1); //time step
	const double step_duration_ = (0.1); //step duration in ms
	const int t_ref_ = (20); //period where neuron is refractory in time steps(20*h_) =2ms
	const double J_ = (0.1); //post-synaptic potential amplitude
	const int transmission_delay_ = (15); //delay after which spike is transmitted (in steps)
	//integration constants
	double c1_;
	double c2_;


public :
	//Constructor
	Neuron();
	
	//getters and setters
	double getPotential() const;
	int getNb_spikes() const;
	std::vector<double> getSpike_times() const;
	int getTime() const;
	void setV(double);
	void setNb_spikes(int);
	void setTime (int);
	void set_i_ext(double i);
	void recieve_spike(double j, int arrival);
	
	//update method
	bool update();
};

#endif