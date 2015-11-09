#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/Led.h>

/**
 * Basic access to the Turtlebot 2 robot.
 * Ana Cruz-Martín, 2015
 *
 * DISCLAIMER: This is a work-in-progress test code, not finished yet.
 *
 * Based on the information and examples from this webs:
 *
 *   · http://wiki.ros.org/Robots/TurtleBot
 *   · https://github.com/turtlebot/turtlebot/blob/indigo/turtlebot_teleop/src/turtlebot_joy.cpp
 *   · http://answers.ros.org/question/47500/turtlebot-ros-moving-using-twist/
 *   · http://learn.turtlebot.com/
 *   · http://wiki.ros.org/kobuki/Tutorials/Examine%20Kobuki
 *
 * THIS CODE IS NOT FINISHED YET.
 */

int main(int argc, char **argv)
{
  ros::init(argc, argv , "turtlebot2_move");
  ros::NodeHandle n;

  // Topics of the mobile base.
  ros::Publisher mobile_base_led2= n.advertise<kobuki_msgs::Led>("/mobile_base/commands/led2", 1000);
  ros::Publisher mobile_base_vel = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1000);
  ros::Rate loop_rate(10);

 
  /**
   * Main code.
   */

  geometry_msgs::Twist newTwist;	/* Message with the speed values */
  newTwist.linear.x = 0.1;
  newTwist.linear.y = 0.0;
  newTwist.linear.z = 0.0;
  newTwist.angular.x = 0.0;
  newTwist.angular.y = 0.0;
  newTwist.angular.z = 0.0;
  int count = 0;
  kobuki_msgs::Led led;
  while (ros::ok() && count<=30)
  {
    led.value = count % 4;
    mobile_base_led2.publish(led);
    mobile_base_vel.publish(newTwist);
  
    if (count == 29)
    {
       newTwist.linear.x = 0.0;
    }

    count++;
    ROS_INFO("Count: %d\n",count);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
