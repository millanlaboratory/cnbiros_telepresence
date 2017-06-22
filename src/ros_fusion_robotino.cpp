#include <ros/ros.h>
#include "cnbiros_navigation/SimpleFusion.hpp"

typedef cnbiros::navigation::SimpleFusion SimpleFusion;

int main(int argc, char** argv) {

	ros::init(argc, argv, "fusion");
	ros::NodeHandle node("~");
	ros::Rate r(20);

	SimpleFusion repellors(&node, "repellors");
	SimpleFusion attractors(&node, "attractors");

	// Repellors list
	repellors.Add("/robotino/infrared", SimpleFusion::AsPointCloud); 
	repellors.Add("/robotino/kinect", SimpleFusion::AsLaserScan); 

	// Attractors list
	attractors.Add("/bci/bci_discrete",  SimpleFusion::AsPoint); 
	attractors.Add("/bci/bci_continous", SimpleFusion::AsPoint); 


	
	while(node.ok()) {


		repellors.Process();
		attractors.Process();

		r.sleep();
		ros::spinOnce();
	}

	return 0;

}
