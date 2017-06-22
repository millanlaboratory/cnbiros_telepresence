#ifndef CNBIROS_TELEPRESENCE_BCICONTROL_CPP
#define CNBIROS_TELEPRESENCE_BCICONTROL_CPP

#include "cnbiros_telepresence/BciControl.hpp"


namespace cnbiros {
	namespace telepresence {

BciControl::BciControl(ros::NodeHandle* node) : cnbiros::core::NodeInterface(node, "bcicontrol") {
	
	this->rossubs_ = new cnbiros::core::Subscribers(node);
	this->rospubs_ = new cnbiros::core::Publishers(node);

	this->rossubs_->Add(node->getNamespace()+"/tid/cnbi2ros", &BciControl::on_received_tid, this);
	this->rossubs_->Add(node->getNamespace()+"/tic/cnbi2ros", &BciControl::on_received_tic, this);

	this->rospubs_->Add<geometry_msgs::Point32>(node->getNamespace()+"/bci_discrete");
	this->rospubs_->Add<geometry_msgs::Point32>(node->getNamespace()+"/bci_continuous");

}

BciControl::~BciControl(void) {
	delete this->rossubs_;
	delete this->rospubs_;
}

void BciControl::ConfigTicMessage(const std::string& name, const std::string& label) {
	this->icname_  = name;
	this->iclabel_ = label;
	
}

void BciControl::on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg) {
	
	int event;
	float angle;
	bool iscommand = false;

	event = (*msg).event;

	switch(event) {
		case CNBIROS_BCICONTROL_EVENT_START:
			ROS_INFO("Event start");
			break;
		case CNBIROS_BCICONTROL_EVENT_STOP:
			ROS_INFO("Event stop");
			break;
		case CNBIROS_BCICONTROL_EVENT_QUIT:
			ROS_INFO("Event quit");
			break;
		case CNBIROS_BCICONTROL_EVENT_LEFT:
			ROS_INFO("Command turn left");
			angle = CNBIROS_BCICONTROL_COMMAND_ANGLE;
			iscommand = true;
			break;
		case CNBIROS_BCICONTROL_EVENT_RIGHT:
			ROS_INFO("Command turn right");
			angle = -CNBIROS_BCICONTROL_COMMAND_ANGLE;
			iscommand = true;
			break;
		case CNBIROS_BCICONTROL_EVENT_FORWARD:
			ROS_INFO("Command go forward");
			angle = 0.0f;
			iscommand = true;
			break;
		case CNBIROS_BCICONTROL_EVENT_BACKWARD:
			ROS_INFO("Command go backward");
			break;
	}

	if(iscommand == true) {
		this->cmd_discrete_.point.x = CNBIROS_BCICONTROL_COMMAND_RADIUS*cos(angle);
		this->cmd_discrete_.point.y = CNBIROS_BCICONTROL_COMMAND_RADIUS*sin(angle);
		this->cmd_discrete_.point.z = 0.0f;
		this->cmd_discrete_.isvalid = true;
		this->cmd_discrete_.time = ros::Time::now();
	}


}

void BciControl::on_received_tic(const cnbiros_bci::TicMessage::ConstPtr& msg) {

	cnbiros::bci::TicTools tool;

	float value;
	geometry_msgs::Point32 point;
	cnbiros_bci::TicMessage data = *msg;
	

	value = tool.GetValue(data, this->icname_, this->iclabel_);

	point.x = CNBIROS_BCICONTROL_COMMAND_RADIUS*cos(value);
	point.y = CNBIROS_BCICONTROL_COMMAND_RADIUS*sin(value);
	point.z = 0.0f;

	this->rospubs_->Publish(this->GetNode()->getNamespace()+"/bci_continuous", point);

}


void BciControl::onRunning(void) {
	
	ros::Duration elapsed;
	ros::Time 	  current = ros::Time::now();

	elapsed = current - this->cmd_discrete_.time;


	if(this->cmd_discrete_.isvalid == true) {
		if(elapsed.toSec() > CNBIROS_BCICONTROL_COMMAND_TIMEOUT) {
			this->cmd_discrete_.point.x = 0.0f;
			this->cmd_discrete_.point.y = 0.0f;
			this->cmd_discrete_.isvalid = false;
		}
		
		this->rospubs_->Publish(this->GetNode()->getNamespace()+"/bci_discrete", this->cmd_discrete_.point);
			
	}
		
}

	}
}

#endif
