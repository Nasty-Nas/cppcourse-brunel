# CS-116 Neuron Simulation Project

This project is a simulation of a network of neurons based on Brunel's model. We have billions of neurons in our brain, here we limit the size of our network to 12500 neurons, randomly connected to each other.
The neurons have a membrane potential that evolves over the time of the simulation. When a neuron's membrane potential reaches a certain thershold, 
the neuron spikes, transmitting a signal to all the neurons it is connected to.
During the simulation, we record every time a neuron spikes, and at the end we can plot these results to visualize them better.


## Running the simulation

Go to the build directory, use comand "cmake.." then "make" then run "./neuron"
RUN TIME : approximately 2 min.
By default we run the simulation over 100ms, if you want to edit this value, open main.cpp and edit "t_stop" value to 10*(time in ms)
Note : increasing simultation time will increase the run time.
At the end of the simulation, you can view the results in the file "spikes.gdf" in build directory.
You can also use the command "make doc" for an Html file documenting the code (this file will be created in the html directory)

The results will be different each time we run the simulation as the connections in the network are generated randomly.
You can see an exmaple of results in the PDF file.

## Running the tests

To run the tests, run the executable file "./neuron_unittest"
You can see the different tests created in the "neuron_unittest.cpp" file


## Authors

* **Anas Seddiki**


