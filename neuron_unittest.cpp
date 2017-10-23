#include <iostream>
#include "neuron.h"
#include "gtest/gtest.h"
#include <cmath>

TEST (NeuronTest, MembranePotential) {
	Neuron n;
	n.set_i_ext(1.0);

	//First update test
	n.update();
	EXPECT_EQ(20.0*(1.0-(exp(-0.1/20.0))), n.getPotential());
}