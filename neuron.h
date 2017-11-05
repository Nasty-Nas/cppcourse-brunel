#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>

/**
 * This class is a simplified representation of a neuron.
 * A neuron has a membrane potential that evolves over time
 * the neuron can spike and send a signal to other neurons it is connected to
 * 
 * @author Seddiki Anas
 */
class Neuron {
	
private :
	double potential_; //!< membrane potential (mV)
	int nb_spikes_; //!< number of times the neuron has spiked
	std::vector<double> spike_times_; //!< table that contains all the times (in steps) at which the neuron has spiked
	int clock_; //!< internal time of neuron in steps
	bool isRefractory_; //!< true = neuron is in refractory period
	int ref_period_; //!< value going form [0 to t_ref_], when == to t_ref_ -> end of refractory period
	std::vector<double> spike_buff_; //!< A buffer for incoming spikes
	double i_ext_; //!< external current
	bool isExcitatory_; //!< true if the neuron is excitatory, false if neuron is inhibitory
	std::vector<int> target_co_; //!< target neurons this neuron is connected to
	const int c_excitatory_ = 1000; //!< number of incoming excitatory connections to a neuron
	const double v_ext_ = (threshold_ / (c_excitatory_ * (J_excitatory_ * tau_ * 0.001))); //!<  frequency of external input (0.001 to get tau in seconds)

	//////////////
	//constants //
	//////////////
	const double threshold_ = 20.0; //!< potential for which the neuron spikes (mV)
	const double tau_ = 20.0; //!< membrane time constant(time steps)
	const double R_ = 20.0; //!< Memebrane resistance
	const double step_duration_ = 0.1; //!< step duration in ms
	const int t_ref_ = 20; //!< period where neuron is refractory in time steps
	const int transmission_delay_ = 15; //!< delay after which spike is transmitted (in steps)
	const double g_ = 5.0; //!< relative strength of inhibitory synapses
	const double J_excitatory_ = 0.1; //!< post-synaptic potential amplitude for excitatory neruon
	const double J_inhibitory_ = -g_ * J_excitatory_; //!< post-synaptic potential amplitude for inhibitory neruon
	
	double c1_; //!< integration constant 1
	double c2_; //!< integration constant 2


public :
	
	/**
	 * Constructor
	 * @param type type of neuron (excitatory = true or inhibitory = false)
	 */
	Neuron(bool type);
	
	 /// Default destructor 
	virtual ~Neuron() = default;
	
	/// Gets the neuron's membrane potential
	double getPotential() const;
	/// Gets the number of times the neuron has spiked
	int getNb_spikes() const;
	/// Gets the times (in steps) at which the neuron has spiked
	std::vector<double> getSpike_times() const;
	/// Gets the time step at which the neuron currently is
	int getTime() const;

	/**
	 * Tells us which type of neuron this is
	 * @return true if the neuron is excitatory, false if it is inhibitory
	 */
	bool isExcitatory() const;

	/**
	 * Allows us to set the external current to a certain value
	 * @param i what we want to set the potential to
	 */
	void set_i_ext(double i);

	/**
	 * Stores incoming spikes in a buffer
	 * @param j weight of post synaptic potential
	 * @param arrival time at which the spike arrives
	 */
	void recieve_spike(double j, int arrival);

	/// Gets the indexes of the target neurons that this neuron is connected to
	std::vector<int> getTarget_co() const;
	/**
	 * Allows us to add any given neuron as a target of this neuron
	 * @param int index of the target neuron
	 */
	void setTarget_co(int);

	/// Gets the neuron's post-synaptic potential amplitude depending on if it is inhibitory or excitatory
	double getJ() const;

	/**
	 * Generates random background noise
	 * using a poison ditribution
	 * @return background noise
	 */
	double get_background_noise();

	/**
	 * Updates a neuron's membrane potential over one time step and checks for spike condition,
	 * if the neuron spikes, it sends a signal to the target neurons it is connected to and
	 * it's membrane potential is reset to 0 for a certain refractory period
	 * @return true if the neuron spiked at this time step, false if it didn't spike
	 */
	bool update();

	/**
	 * Same as update, but here the background noise is neglected
	 * This function serves for testing purposes only
	 * @return true if the neuron spiked at this time step, false if it didn't spike
	 * @see update()
	 */
	bool update_no_noise();
};

#endif