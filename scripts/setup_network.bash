#!/usr/bin/env bash


localhost_flag=0
robothost_flag=0
localhost_ip=""
robothost_ip=""


if grep -q "$1" /etc/hosts; then
	localhost_ip=$(grep -w "$1" /etc/hosts | awk '{print $1}')
	localhost_flag=1
fi

if grep -q "robot" /etc/hosts; then
	robothost_ip="$(grep -w "robot" /etc/hosts | awk '{print $1}')"
	robothost_flag=1
fi


export ROS_HOSTNAME=$1
export ROS_MASTER_URI=http://robot:11311

echo "########################################"
echo "#         ROS Network settings         #"
echo "########################################"
echo ""
echo " ROS_HOSTNAME=$1 ($localhost_ip)"
echo " ROS_MASTER_URI=http://robot:11311 ($robothost_ip)"
echo ""

if  [ -z $localhost_ip ]; then
	echo " Warning: No '$1' hostname found in /etc/hosts"
fi

if [ "$1" != 'robot' ]; then
	if [ -z $robothost_flag ]; then
		echo " Warning: No 'robot' hostname found /etc/hosts"
	fi
fi
echo "########################################"
