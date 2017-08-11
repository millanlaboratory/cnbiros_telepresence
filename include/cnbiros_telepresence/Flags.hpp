#ifndef CNBIROS_TELEPRESENCE_FLAGS_HPP
#define CNBIROS_TELEPRESENCE_FLAGS_HPP

#define CNBIROS_BCIBRIDGE_INPUT_MIN 	-1.0f 		// Min value in TiC message from cnbiloop
#define CNBIROS_BCIBRIDGE_INPUT_MAX		 1.0f		// Max value in TiC message from cnbiloop
#define CNBIROS_BCIBRIDGE_ANGLE_MIN		-M_PI/4.0f	// Min angle in ROS environment
#define CNBIROS_BCIBRIDGE_ANGLE_MAX		 M_PI/4.0f	// Max angle in ROS environment
#define CNBIROS_BCIBRIDGE_DISTANCE 		 0.5f		// Distance from the center [m]
#define CNBIROS_BCIBRIDGE_TIMEOUT		 1.0f		// Timeout for discrete command [s]

#define CNBIROS_BCIBRIDGE_TOPIC_TIC_CNBI2ROS	"/rostic_cnbi2ros"
#define CNBIROS_BCIBRIDGE_TOPIC_TID_CNBI2ROS 	"/rostid_cnbi2ros"
#define CNBIROS_BCIBRIDGE_TOPIC_DISCRETE		"/bci_discrete"
#define CNBIROS_BCIBRIDGE_TOPIC_CONTINUOUS 		"/bci_continuous"

#define CNBIROS_BCIBRIDGE_EVENT_START		25345 // hexadecimal: "0x6301"
#define CNBIROS_BCIBRIDGE_EVENT_STOP		25346 // hexadecimal: "0x6302"
#define CNBIROS_BCIBRIDGE_EVENT_QUIT		25347 // hexadecimal: "0x6303"
#define CNBIROS_BCIBRIDGE_EVENT_LEFT		25348 // hexadecimal: "0x6304"
#define CNBIROS_BCIBRIDGE_EVENT_RIGHT		25349 // hexadecimal: "0x6305"
#define CNBIROS_BCIBRIDGE_EVENT_FORWARD		25350 // hexadecimal: "0x6306"
#define CNBIROS_BCIBRIDGE_EVENT_BACKWARD	25351 // hexadecimal: "0x6307"
#define CNBIROS_BCIBRIDGE_EVENT_RESUME		25352 // hexadecimal: "0x6308"
#define CNBIROS_BCIBRIDGE_EVENT_PAUSE		25353 // hexadecimal: "0x6309"



#endif
