#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
    // Initialize the simple_navigation_goals node
    ros::init(argc, argv, "pick_objects");

    //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

    // Wait 5 sec for move_base action server to come up
    while(!ac.waitForServer(ros::Duration(5.0))) {
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal pickupGoal;

    // set up the frame parameters
    pickupGoal.target_pose.header.frame_id = "map";
    pickupGoal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    pickupGoal.target_pose.pose.position.x = 5.1;
    pickupGoal.target_pose.pose.position.y = 1.5;
    pickupGoal.target_pose.pose.orientation.w = 1.0;

    // Send the pickupGoal position and orientation for the robot to reach
    ROS_INFO("Sending pickup location");
    ac.sendGoal(pickupGoal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Arrived at pickup location, securing package");
    else
        ROS_INFO("Orientation deficit - failed to find pickup location");


    move_base_msgs::MoveBaseGoal dropoffGoal;

    // set up the frame parameters
    dropoffGoal.target_pose.header.frame_id = "map";
    dropoffGoal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    dropoffGoal.target_pose.pose.position.x = -1.7;
    dropoffGoal.target_pose.pose.position.y = -0.5;
    dropoffGoal.target_pose.pose.orientation.w = 1.0;

    // Send the dropoffGoal position and orientation for the robot to reach
    ROS_INFO("Sending dropoff location");
    ac.sendGoal(dropoffGoal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Arrived at dropoff location, securing package");
    else
        ROS_INFO("Orientation deficit - failed to find dropoff location");

    return 0;

}
