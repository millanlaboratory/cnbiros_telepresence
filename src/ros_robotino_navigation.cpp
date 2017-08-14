#include <ros/ros.h>
#include "cnbiros_navigation/ForceField.hpp"

typedef cnbiros::navigation::ForceField ForceField;

int main(int argc, char** argv) {

	ros::init(argc, argv, "navigation");
	ros::NodeHandle node;

	ForceField forcefield(&node);
	forcefield.SetRate(40);

	forcefield.Start();



	return 0;

}
