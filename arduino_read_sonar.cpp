#include "ros/ros.h"
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include "std_msgs/Float32.h"

/**
 * The node reads values from an sonar connected to an Arduino.
 * 
 * Once those values are read, they are used to compute to speed values that will be sent to Turtlesim node.
 *  
 * This code is based on the tutorials at wiki.ros.org
 * 
 * Ana Cruz Martín, 2016
 */

std_msgs::Float32 sonarCallbackReading;	
using namespace std;


void getSonarCallback(const std_msgs::Float32 &sonarReading)
{
  ROS_INFO("Sonar Reading:%f\n",sonarReading.data);
  sonarCallbackReading.data = sonarReading.data;
}


int main(int argc, char **argv)
{
  /**
   * ros::init()
   * 
   * Initialization
   *
   */
  ros::init(argc, argv, "arduino_read_sonar"); 

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * Topics: advertising and subscribing
   */
  
  ros::Publisher v_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
  ros::Rate loop_rate(10);

  ros::Subscriber p_sub = n.subscribe("sonar_topic",1000,getSonarCallback);

  
  ROS_INFO("Entering main loop\n");
  while (ros::ok())
  {   
    geometry_msgs::Twist miVel;

    miVel.linear.x = 0.0;
    miVel.linear.y = 0.0;
    miVel.linear.z = 0.0;
    miVel.angular.x = 0.0;
    miVel.angular.y = 0.0;
    miVel.angular.z = 0.0;
   
    if (sonarCallbackReading.data < 25)	// Too close, turn back!!
    {
    	miVel.linear.x = -1.0;
        miVel.angular.z = -0.5;
    }
    else if ((sonarCallbackReading.data >= 25) && (sonarCallbackReading.data < 50)) // Still too close, move slowly
    {
   	 miVel.linear.x = 0.5;
         miVel.angular.z = 0.4;
    }
    else if ((sonarCallbackReading.data >= 50) && (sonarCallbackReading.data < 75)) // Not too close, move not so slowly
    {
   	 miVel.linear.x = 1.0;
         miVel.angular.z = 0.8;
    }
    else
    {
	 miVel.linear.x = 2.0;	// Far enough, go ahead!!
         miVel.angular.z = 1.8;
    }
    v_pub.publish(miVel);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
