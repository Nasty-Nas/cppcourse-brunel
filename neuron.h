#ifndef NEURON_
#define NEURON_

#include <iostream>
#include <vector>


class Neuron {
	
	private:
	
	double V_;
	int nb_spikes_;
	vector<int> spike_times_;
<<<<<<< HEAD
	int time_;
=======
	double ref_;
	double threshold_ = 20;
	int time_;
	double tau_ = 0.002;
>>>>>>> dcba6491ebbbc270fa901ca9e3529b6bd41cd6e5
	
	public:
	
	//Constructor
	Neuron(int t);
	
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
