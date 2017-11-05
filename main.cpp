#include <iostream>
#include <fstream>

#include "Network.h"

using namespace std;

int main()
{

	int t_stop = 1000; // total simulation time (in steps) = 100ms

	Network network;
	network.update(t_stop);

	return 0;
}
