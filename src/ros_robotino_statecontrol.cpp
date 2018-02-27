#include <ros/ros.h>
#include "cnbiros_telepresence/StateControl.hpp"


int main(int argc, char** argv) {

	ros::init(argc, argv, "state_control");
	ros::NodeHandle node;


	cnbiros::telepresence::StateControl manager(&node);
	manager.SetRate(50);

	manager.Run();

	ros::shutdown();
	return 0;
}
