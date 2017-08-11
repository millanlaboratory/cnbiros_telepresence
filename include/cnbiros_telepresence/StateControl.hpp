#ifndef CNBIROS_TELEPRESENCE_STATECONTROL_HPP
#define CNBIROS_TELEPRESENCE_STATECONTROL_HPP

#include <ros/ros.h>

#include "cnbiros_core/NodeInterface.hpp"
#include "cnbiros_core/Subscribers.hpp"
#include "cnbiros_bci/TidMessage.h"

#include "cnbiros_telepresence/Flags.hpp"

namespace cnbiros {
	namespace telepresence {

class StateControl : public cnbiros::core::NodeInterface {

	public:
		StateControl(ros::NodeHandle* node, std::string name = "state_control");
		//virtual ~StateControl(void);

	private:
		void on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg);
		void call_state_service(cnbiros_core::SetStateSrv srv);

		cnbiros::core::Subscribers* rossubs_;
		ros::ServiceClient			rossrv_state_client_;
};	

	}
}

#endif