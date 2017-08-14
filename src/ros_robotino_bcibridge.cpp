#include <ros/ros.h>
#include "cnbiros_telepresence/BciBridge.hpp"


int main(int argc, char** argv) {

	ros::init(argc, argv, "bci_bridge");
	ros::NodeHandle node("~");


	cnbiros::telepresence::BciBridge bci(&node);
	bci.SetRate(20);

	bci.ConfigTicMessage("cl_ticsender", "0x0580");

	bci.Run();



	ros::shutdown();
	return 0;
}
