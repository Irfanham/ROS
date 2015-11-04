#include "ros/ros.h"
#include "std_msgs/Float64.h"

/**
 * Basic homing for the WidowX arm. Joints 1 to 5 are set to 0 degrees.
 * Ana Cruz-Martín, 2015
 * 
 * DISCLAIMER: This is a work-in-progress test code, not finished yet.
 * 
 * This code must be integrated into a ros package, and then called with rosrun,
 * while the widowx arm software by Robotnik is running.
 * https://github.com/RobotnikAutomation/widowx_arm
 * 
 * For videos and further information
 * http://jafma.net/ana/theweekendarchaeologist/?p=564
 *
 * TO DO:
 * - Clean and organize code
 * - Use services for relaxing joints
 * - Open/close gripper
 * - Read joints values
 * - Create a proper launch file
 * - rviz integration
 */

int main(int argc, char **argv)
{
  ros::init(argc, argv , "widowx_arm_home");
  ros::NodeHandle n;

  // Topics of the joints.
  ros::Publisher joint1 = n.advertise<std_msgs::Float64>("/arm_1_joint/command", 1000);
  ros::Publisher joint2 = n.advertise<std_msgs::Float64>("/arm_2_joint/command", 1000);
  ros::Publisher joint3 = n.advertise<std_msgs::Float64>("/arm_3_joint/command", 1000);
  ros::Publisher joint4 = n.advertise<std_msgs::Float64>("/arm_4_joint/command", 1000);
  ros::Publisher joint5 = n.advertise<std_msgs::Float64>("/arm_5_joint/command", 1000);
  ros::Rate loop_rate(10);

  /**
   * Main code.
   */

  std_msgs::Float64 degrees;
  degrees.data = 0;
  int count = 0;
  while (ros::ok() && count<=200)
  {
    joint2.publish(degrees); /* Shoulder, [-pi/2, pi/2] */
    joint3.publish(degrees); /* Elbow , [-pi/2, pi/2]  */
    joint4.publish(degrees); /* Wrist (pitch), [-pi/2, pi/2]  */
    joint5.publish(degrees); /* Wrist (roll), [-pi/2, pi/2]  */
    joint1.publish(degrees); /* Waist, [-pi/2, pi/2]  */
    ROS_INFO("Count: %d\n",count);
    count++;
 
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
