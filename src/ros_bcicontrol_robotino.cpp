#include <ros/ros.h>
#include "cnbiros_telepresence/BciControl.hpp"


int main(int argc, char** argv) {

	ros::init(argc, argv, "bcicontrol");
	ros::NodeHandle node("~");


	cnbiros::telepresence::BciControl bci(&node);
	bci.SetRate(20);

	bci.ConfigTicMessage("cl_ticsender", "0x0580");

	bci.Start();



	ros::shutdown();
	return 0;
}
