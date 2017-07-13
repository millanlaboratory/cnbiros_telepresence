#ifndef CNBIROS_TELEPRESENCE_BCIBRIDGE_HPP
#define CNBIROS_TELEPRESENCE_BCIBRIDGE_HPP

#include <ros/ros.h>
#include <geometry_msgs/Point32.h>
#include "cnbiros_core/NodeInterface.hpp"
#include "cnbiros_core/Subscribers.hpp"
#include "cnbiros_core/Publishers.hpp"
#include "cnbiros_bci/TidMessage.h"
#include "cnbiros_bci/TicMessage.h"
#include "cnbiros_bci/TicTools.hpp"
#include "cnbiros_bci/TidTools.hpp"

#include "cnbiros_fusion/ResetGridSrv.h"

#include "cnbiros_telepresence/Flags.hpp"
#include "cnbiros_telepresence/SetInputRangeSrv.h"
#include "cnbiros_telepresence/SetAngleRangeSrv.h"
#include "cnbiros_telepresence/SetDistanceSrv.h"

namespace cnbiros {
	namespace telepresence {

struct CmdDiscrete {
	geometry_msgs::Point32 point;
	bool isvalid;
	ros::Time time;
};

class BciBridge : public cnbiros::core::NodeInterface {
	
	public:
		BciBridge(ros::NodeHandle* node);
		virtual ~BciBridge(void);

		void SetInputRange(float value_min, float value_max);
		void SetAngleRange(float angle_min, float angle_max);
		void SetDistance(float distance);

		void ConfigTicMessage(const std::string& name, const std::string& label);

	protected:
		virtual void on_received_tid(const cnbiros_bci::TidMessage::ConstPtr& msg);
		virtual void on_received_tic(const cnbiros_bci::TicMessage::ConstPtr& msg);
		virtual void onRunning(void);

		virtual bool on_set_input_range(cnbiros_telepresence::SetInputRangeSrv::Request& req,
										cnbiros_telepresence::SetInputRangeSrv::Response& res);
		virtual bool on_set_angle_range(cnbiros_telepresence::SetAngleRangeSrv::Request& req,
										cnbiros_telepresence::SetAngleRangeSrv::Response& res);
		virtual bool on_set_distance(cnbiros_telepresence::SetDistanceSrv::Request& req,
									 cnbiros_telepresence::SetDistanceSrv::Response& res);


	private:
		cnbiros::core::Subscribers*	rossubs_;
		ros::Publisher 				rospub_discrete_;
		ros::Publisher 				rospub_continuous_;
		ros::ServiceServer			rossrv_input_range_;
		ros::ServiceServer			rossrv_angle_range_;
		ros::ServiceServer			rossrv_distance_;
		ros::ServiceClient 			rossrv_reset_client_;

		std::string 	icname_;
		std::string 	iclabel_;

		CmdDiscrete 	cmd_discrete_;

		float 	value_min_;
		float 	value_max_;
		float 	angle_min_;
		float 	angle_max_;
		float 	distance_;
};


	}
}


#endif
