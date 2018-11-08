#!/bin/sh
# xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/nvidia/catkin_ws/src/World/Berkach/Berkach2/Berkach2" &
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/nvidia/catkin_ws/src/World/SimpleWorld/SimpleWorld" &
sleep 8
xterm -e "roslaunch gmapping.launch" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun wall_follower wall_follower" &
