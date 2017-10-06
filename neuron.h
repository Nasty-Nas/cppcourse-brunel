#ifndef NEURON_
#define NEURON_

#include <iostream>
#include <vector>


class Neuron {
	
	private:
	
	double V_;
	int nb_spikes_;
	vector<int> spike_times_;
	int time_;
	
	public:
	
	//getters and setters
	double getV const();
	int getNb_spikes const();
	vector<int> getSpike_times const();
	int getTime const();
	void setV(double);
	void setNb_spikes(int);
	void setTime (int);
	
	//update method
	void update ();
	
	
	
	
	
	
	



};
