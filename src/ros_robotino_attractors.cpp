#include <ros/ros.h>
#include "cnbiros_fusion/SimpleFusion.hpp"

typedef cnbiros::fusion::SimpleFusion SimpleFusion;

int main(int argc, char** argv) {

	ros::init(argc, argv, "attractors");
	ros::NodeHandle node;
	ros::Rate r(20);

	SimpleFusion attractors(&node, "attractors");

	// Attractors list
	attractors.AddSource("/bci_discrete",   SimpleFusion::AsPoint); 
	attractors.AddSource("/bci_continuous", SimpleFusion::AsPoint); 

	attractors.Start();
	
	return 0;

}
