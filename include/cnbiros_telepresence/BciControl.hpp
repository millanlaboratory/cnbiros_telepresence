#ifndef CNBIROS_TELEPRESENCE_BCICONTROL_HPP
#define CNBIROS_TELEPRESENCE_BCICONTROL_HPP

#include <ros/ros.h>
#include <geometry_msgs/Point32.h>
#include "cnbiros_core/NodeInterface.hpp"
#include "cnbiros_core/Subscribers.hpp"
#include "cnbiros_core/Publishers.hpp"
#include "cnbiros_bci/TidMessage.h"
#include "cnbiros_bci/TicMessage.h"
#include "cnbiros_bci/TicTools.hpp"
#include "cnbiros_bci/TidTools.hpp"

#include "cnbiros_navigation/ResetGridService.h"
#include "cnbiros_telepresence/Flags.hpp"

namespace cnbiros {
	namespace telepresence {

struct CmdDiscrete {
	geometry_msgs::Point32 point;
	bool isvalid;
	ros::Time time;
};

class BciControl : public cnbiros::core::NodeInterface {
	
	public:
		BciControl(ros::NodeHandle* node);
		virtual ~BciControl(void);

		void ConfigTicMessage(const std::string& name, const std::string& label);

	protected:
		virtual void on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg);
		virtual void on_received_tic(const cnbiros_bci::TicMessage::ConstPtr& msg);
		virtual void onRunning(void);

	private:
		cnbiros::core::Subscribers*	rossubs_;
		cnbiros::core::Publishers* 	rospubs_;
		ros::ServiceClient 			rossrv_reset_;

		std::string 	icname_;
		std::string 	iclabel_;

		CmdDiscrete 	cmd_discrete_;
};


	}
}


#endif
