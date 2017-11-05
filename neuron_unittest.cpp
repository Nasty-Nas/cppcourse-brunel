#include <iostream>
#include "neuron.h"
#include "gtest/gtest.h"
#include <cmath>

TEST (NeuronTest, PositiveInput) {
	Neuron n(true);
	n.set_i_ext(1.0);

	//First update test
	n.update_no_noise();
	EXPECT_EQ(20.0*(1.0-(exp(-0.1/20.0))), n.getPotential());

	//Test after several updates
	for (int i = 0; i < 10000; ++i)
	{
		n.update_no_noise();
	}
	//With an external current of 1.0, the membrane potential should tend to 20 (threshold),
	//but should never reach it, so the neuron should not spike
	EXPECT_EQ(0, n.getNb_spikes());
	EXPECT_GT(1E-3, std::fabs(19.999 - n.getPotential()));

	//With an external current of 0.0, the membrane potential should tend towards 0.
	n.set_i_ext(0.0);
	for (int i = 0; i < 3000; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_NEAR(0, n.getPotential(), 1E-3);
}

TEST (NeuronTest, NegativeInput) {
	Neuron n(true);
	n.set_i_ext(-1.0);

	//First update test
	n.update_no_noise();
	EXPECT_EQ(-20.0*(1.0-(exp(-0.1/20.0))), n.getPotential());

	//Test after several updates
	for (int i = 0; i < 10000; ++i)
	{
		n.update_no_noise();
	}
	//With an external current of 1.0, the membrane potential should tend to -20 (threshold),
	//but should never reach it, so the neuron should not spike
	EXPECT_EQ(0, n.getNb_spikes());
	EXPECT_GT(1E-3, std::fabs(-19.999 - n.getPotential()));

	//With an external current of 0.0, the membrane potential should tend towards 0.
	n.set_i_ext(0.0);
	for (int i = 0; i < 3000; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_NEAR(0, n.getPotential(), 1E-3);
}

TEST (NeuronTest, SpikeTimes) {
	Neuron n(true);
	n.set_i_ext(1.01);
	//We know that for a current of 1.01, spikes occure at 92.4ms, 186.8ms, 281.2ms, 375.6ms

	//testing first spike time
	for (int i = 0; i < 924; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_EQ(0, n.getNb_spikes());
	n.update_no_noise();
	EXPECT_EQ(1, n.getNb_spikes());
	EXPECT_EQ(0.0, n.getPotential()); //testing if potential resets after spike

	//testing second spike time
	for (int i = 0; i < 943; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_EQ(1, n.getNb_spikes());
	n.update_no_noise();
	EXPECT_EQ(2, n.getNb_spikes());

	//testing third spike time
	for (int i = 0; i < 943; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_EQ(2, n.getNb_spikes());
	n.update_no_noise();
	EXPECT_EQ(3, n.getNb_spikes());

	//testing fourth spike time
	for (int i = 0; i < 943; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_EQ(3, n.getNb_spikes());
	n.update_no_noise();
	EXPECT_EQ(4, n.getNb_spikes());

}

TEST (NeuronTest, SpikeNumber) {
	Neuron n(true);
	n.set_i_ext(1.01);

	for (int i = 0; i < 4000; ++i)
	{
		n.update_no_noise();
	}
	EXPECT_EQ(4, n.getNb_spikes());
}

TEST (TwoNeurons, NoPSSpike) {
	Neuron n1(true), n2(true);
	int delay = 15;
	n1.set_i_ext(1.01);

	for (int i = 0; i <925+delay; ++i)
	if(n1.update_no_noise())
	{
		n2.recieve_spike(0.1, i + delay);
		EXPECT_EQ(0.0, n1.getPotential());
	}
	n2.update();
}

TEST (TwoNeurons, WithPSSpike) {
	Neuron n1(true), n2(true);
	int delay = 15;
	n1.set_i_ext(1.01);
	n2.set_i_ext(1.0);

	for (int i = 0; i < 1869+delay; ++i)
	{
		if (n1.update_no_noise())
		{
			n2.recieve_spike(0.1, i + delay);
			EXPECT_EQ(0.0, n1.getPotential());
		}
		n2.update_no_noise();
	}
	EXPECT_EQ(0, n2.getNb_spikes());
	n2.update_no_noise();
	EXPECT_EQ(0, n2.getPotential());
	EXPECT_EQ(1, n2.getNb_spikes());
}

TEST (NeuronTest, RecieveSpike) {

	Neuron n(true);
	int delay = 15;
	double J = 0.1;

	//make the neuron recieve a spike with weight 0.1 and delay 15 steps
	n.recieve_spike(J, delay);

	//update the neuron one step past the delay
	for (int i = 0; i < (delay + 1); ++i)
	{
		n.update_no_noise();
	}

	//check if its membrane potential is equal to the spike recieved
	EXPECT_EQ(J, n.getPotential());
}