#include <iostream>
#include <fstream>
#include "Neuron.h"
//#include "Neuron.cpp" //Cmake
#include "Network.h"
//#include "Network.cpp"

using namespace std;

int main()
{
	int i_start = 1000; //step where current starts
	int i_stop = 4000; //step where current ends
	int t_end = 5000; // total simulation time
	double i_ext = 1.01; //Amplitude of the current

	/*cout << "Enter external current : ";
	cin >> Iext;

	cout << "Enter simulation start time : ";
	cin >> t_start;
	
	do
	{
		cout << "Enter simulation end time : ";
		cin >> t_end;
		if (t_end < t_start)
		{
			cerr << "Error, end time has to be greater than start time" << endl;
		}
	} while (t_end < t_start);
	*/

	ofstream outFile;
	outFile.open("data.dat");

	cout << "I ext = " << i_ext << '\n';
	
	Network network;

	for (int t = 0; t < t_end; ++t)
	{
		if (t >= i_start and t <= i_stop)
		{
			network.set_current(1, i_ext);
		}
		else
		{
			network.set_current(1, 0.0);
		}
		network.update(t);
		outFile << t*0.1 << '\t' << network.get_potential(2) << '\n';
	}
/*	do
	{
		n.update(Iext);
		outFile << "Membrane Potential : " << n.getV() << "Time : " << n.getTime() << endl;
	} while (n.getTime() < t_end);
*/	
	outFile.close();
	return 0;
}
