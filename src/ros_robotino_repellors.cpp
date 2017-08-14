#include <ros/ros.h>
#include "cnbiros_fusion/SimpleFusion.hpp"

typedef cnbiros::fusion::SimpleFusion SimpleFusion;

int main(int argc, char** argv) {

	ros::init(argc, argv, "repellors");
	ros::NodeHandle node;
	ros::Rate r(20);

	SimpleFusion repellors(&node, "repellors");

	// Repellors list
	repellors.AddSource("/infrared", SimpleFusion::AsPointCloud); 
	repellors.AddSource("/camera/scan", SimpleFusion::AsLaserScan); 

	repellors.Run();


	return 0;

}
