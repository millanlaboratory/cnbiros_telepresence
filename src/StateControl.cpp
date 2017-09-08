#ifndef CNBIROS_TELEPRESENCE_STATECONTROL_CPP
#define CNBIROS_TELEPRESENCE_STATECONTROL_CPP

#include "cnbiros_telepresence/StateControl.hpp"


namespace cnbiros {
	namespace telepresence {

StateControl::StateControl(ros::NodeHandle* node, std::string name) : cnbiros::core::NodeInterface(node, name) {

	// Adding subscriber list
	this->rossubs_ = new cnbiros::core::Subscribers(node);
	this->rossubs_->Add(CNBIROS_BCIBRIDGE_TOPIC_TID_CNBI2ROS, &StateControl::on_received_tid, this);

	ROS_INFO("Listening for state control events");

	// Adding service clients
	rossrv_state_client_ = node->serviceClient<cnbiros_core::SetStateSrv>("/navigation/set_state");
	rossrv_odom_client_  = node->serviceClient<cnbiros_robotino::SetOdometrySrv>("/robotino/set_odometry");

	reset_odometry();
}		



void StateControl::reset_odometry(){
	
	int event;
	cnbiros_robotino::SetOdometrySrv srv;
	ROS_INFO("Resetting odometry");
	srv.request.x = 0;
	srv.request.y = 0;
	srv.request.z = 0;
	srv.request.phi = 0;
	call_odometry_service(srv);
	
}

void StateControl::on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg){
	
	int event;
	cnbiros_core::SetStateSrv srv;
	
	event = (*msg).event;

	switch(event) {
		case CNBIROS_BCIBRIDGE_EVENT_START:
			ROS_INFO("Command: start");
			reset_odometry();
			srv.request.state = this->DoStart;
			call_state_service(srv);
			break;
		case CNBIROS_BCIBRIDGE_EVENT_STOP:
			ROS_INFO("Command: stop");
			//reset_odometry();
			srv.request.state = this->DoStop;
			call_state_service(srv);
			ros::shutdown();
			break;
		case CNBIROS_BCIBRIDGE_EVENT_RESUME:
			ROS_INFO("Command: resume");
			reset_odometry();
			srv.request.state = this->DoResume;
			call_state_service(srv);
			break;
		case CNBIROS_BCIBRIDGE_EVENT_PAUSE:
			ROS_INFO("Command: pause");
			//reset_odometry();
			srv.request.state = this->DoPause;
			call_state_service(srv);
			break;
		case 25354:
			ROS_INFO("Command: straight");
			srv.request.state = this->DoStraight;
			call_state_service(srv);
			break;
		case 25355:
			ROS_INFO("Command: left");
			srv.request.state = this->DoLeft;
			call_state_service(srv);
			break;
		case 25356:
			ROS_INFO("Command: right");
			srv.request.state = this->DoRight;
			call_state_service(srv);
			break;
	}
}

void StateControl::call_state_service(cnbiros_core::SetStateSrv srv) {
	if (rossrv_state_client_.call(srv)) {
		ROS_INFO("Successful");
	} else {
		ROS_ERROR("Failed to set state");
	}
}

void StateControl::call_odometry_service(cnbiros_robotino::SetOdometrySrv srv) {
	if (rossrv_odom_client_.call(srv)) {
		ROS_INFO("Successful");
	} else {
		ROS_ERROR("Failed to set state");
	}
}


	}
}

#endif