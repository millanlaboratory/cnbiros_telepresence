#include <ros/ros.h>
#include "cnbiros_telepresence/StateControl.hpp"


int main(int argc, char** argv) {

	ros::init(argc, argv, "state_control");
	ros::NodeHandle node;


	cnbiros::telepresence::StateControl manager(&node);
	manager.SetRate(20);

	manager.Start();

	return 0;
}
