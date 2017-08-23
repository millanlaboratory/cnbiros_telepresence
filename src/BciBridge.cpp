#ifndef CNBIROS_TELEPRESENCE_BCIBRIDGE_CPP
#define CNBIROS_TELEPRESENCE_BCIBRIDGE_CPP

#include "cnbiros_telepresence/BciBridge.hpp"


namespace cnbiros {
	namespace telepresence {

BciBridge::BciBridge(ros::NodeHandle* node) : cnbiros::core::NodeInterface(node, "bci_bridge") {

	// Adding subscriber list
	this->rossubs_ = new cnbiros::core::Subscribers(node);
	this->rossubs_->Add(CNBIROS_BCIBRIDGE_TOPIC_TID_CNBI2ROS, &BciBridge::on_received_tid, this);
	this->rossubs_->Add(CNBIROS_BCIBRIDGE_TOPIC_TIC_CNBI2ROS, &BciBridge::on_received_tic, this);

	// Adding publisher list
	this->rospub_discrete_ = node->advertise<geometry_msgs::Point32>(CNBIROS_BCIBRIDGE_TOPIC_DISCRETE, 
																	 CNBIROS_CORE_BUFFER_MESSAGES);
	this->rospub_continuous_ = node->advertise<geometry_msgs::Point32>(CNBIROS_BCIBRIDGE_TOPIC_CONTINUOUS, 
																	   CNBIROS_CORE_BUFFER_MESSAGES);

	// Setting default command remapping
	this->SetInputRange(CNBIROS_BCIBRIDGE_INPUT_MIN, CNBIROS_BCIBRIDGE_INPUT_MAX);
	this->SetAngleRange(CNBIROS_BCIBRIDGE_ANGLE_MIN, CNBIROS_BCIBRIDGE_ANGLE_MAX);
	this->SetDistance(CNBIROS_BCIBRIDGE_DISTANCE);

	// Adding services
	rossrv_input_range_ = node->advertiseService(ros::this_node::getName() + "/set_input_range", 
												 &BciBridge::on_set_input_range, this);
	rossrv_angle_range_ = node->advertiseService(ros::this_node::getName() + "/set_angle_range", 
												 &BciBridge::on_set_angle_range, this);
	rossrv_distance_    = node->advertiseService(ros::this_node::getName() + "/set_distance", 
												 &BciBridge::on_set_distance, this);
	
	rossrv_reset_client_ = node->serviceClient<cnbiros_fusion::ResetGridSrv>("/fusion/reset_grid");
	
}

BciBridge::~BciBridge(void) {
	delete this->rossubs_;
}

void BciBridge::SetInputRange(float value_min, float value_max) {
	this->value_min_ = value_min;
	this->value_max_ = value_max;
}

void BciBridge::SetAngleRange(float angle_min, float angle_max) {
	this->angle_min_ = angle_min;
	this->angle_max_ = angle_max;
}

void BciBridge::SetDistance(float distance) {
	this->distance_ = distance;
}

bool BciBridge::on_set_input_range(cnbiros_telepresence::SetInputRangeSrv::Request& req,
								   cnbiros_telepresence::SetInputRangeSrv::Response& res) {

	this->SetInputRange(req.value_min, req.value_max);
	return true;
}

bool BciBridge::on_set_angle_range(cnbiros_telepresence::SetAngleRangeSrv::Request& req,
								   cnbiros_telepresence::SetAngleRangeSrv::Response& res) {

	this->SetAngleRange(req.angle_min, req.angle_max);
	return true;
}

bool BciBridge::on_set_distance(cnbiros_telepresence::SetDistanceSrv::Request& req,
								cnbiros_telepresence::SetDistanceSrv::Response& res) {

	this->SetDistance(req.distance);
	return true;
}

void BciBridge::ConfigTicMessage(const std::string& name, const std::string& label) {
	this->icname_  = name;
	this->iclabel_ = label;
	
}

void BciBridge::on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg) {
	
	int event;
	float angle;
	bool iscommand = true;

	event = (*msg).event;

	switch(event) {
		case CNBIROS_BCIBRIDGE_EVENT_LEFT:
			ROS_INFO("Command turn left");
			angle = this->angle_min_;
			iscommand = true;
			break;
		case CNBIROS_BCIBRIDGE_EVENT_RIGHT:
			ROS_INFO("Command turn right");
			angle = this->angle_max_;
			iscommand = true;
			break;
		case CNBIROS_BCIBRIDGE_EVENT_FORWARD:
			ROS_INFO("Command go forward");
			angle = 0.0f;
			iscommand = true;
			break;
		default:
			iscommand = false;
			break;
	}

	if(iscommand == true) {
		this->cmd_discrete_.point.x = this->distance_*cos(angle);
		//need sin(-...) since increasing value corresponds to clockwise rotation as opposed to mathematical angle
		this->cmd_discrete_.point.y = this->distance_*sin(-angle);
		this->cmd_discrete_.point.z = 0.0f;
		this->cmd_discrete_.isvalid = true;
		this->cmd_discrete_.time = ros::Time::now();
	}


}

void BciBridge::on_received_tic(const cnbiros_bci::TicMessage::ConstPtr& msg) {

	cnbiros::bci::TicTools tool;

	float value, nvalue, svalue;
	geometry_msgs::Point32 point;
	cnbiros_bci::TicMessage data = *msg;

	value = tool.GetValue(data, this->icname_, this->iclabel_);

	nvalue = (value - this->value_min_)/(this->value_max_ - this->value_min_);
	svalue = nvalue*(this->angle_max_ - this->angle_min_) + this->angle_min_;

	point.x = this->distance_*cos(svalue);
	//need sin(-...) since increasing value corresponds to clockwise rotation as opposed to mathematical angle
	point.y = this->distance_*sin(-svalue);
	point.z = 0.0f;

	this->rospub_continuous_.publish(point);

}

void BciBridge::onRunning(void) {

	cnbiros_fusion::ResetGridSrv srv;
	srv.request.layer = CNBIROS_BCIBRIDGE_TOPIC_DISCRETE;
	srv.request.value = 0.0f;
	
	ros::Duration elapsed;
	ros::Time 	  current = ros::Time::now();

	elapsed = current - this->cmd_discrete_.time;


	if(this->cmd_discrete_.isvalid == true) {
		if(elapsed.toSec() > CNBIROS_BCIBRIDGE_TIMEOUT) {
			ROS_INFO("elapsed");
			this->cmd_discrete_.isvalid = false;
			this->cmd_discrete_.point.x = NAN;
			this->cmd_discrete_.point.y = NAN;
			this->cmd_discrete_.point.z = NAN;

			//if(this->rossrv_reset_client_.call(srv))
			//	ROS_INFO("Reset done");
		}
			
		this->rospub_discrete_.publish(this->cmd_discrete_.point);
	}


		
}

	}
}

#endif
