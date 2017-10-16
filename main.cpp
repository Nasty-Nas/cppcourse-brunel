#include <iostream>
#include <fstream>
#include "neuron.h"
#include "neuron.cpp" //Cmake

using namespace std;

int main()
{
	double Iext;
	double t_start;
	double t_end;

	cout << "Enter external current : ";
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
	
	Neuron n(t_start);
	ofstream outFile;
	outFile.open("Membrane_Potentials.txt");
	
	do
	{
		n.update(Iext);
		outFile << "Membrane Potential : " << n.getV() << "Time : " << n.getTime() << endl;
	} while (n.getTime() < t_end);
	
	outFile.close();
	return 0;
}
