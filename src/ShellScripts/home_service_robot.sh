#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/nvidia/catkin_ws/src/World/SimpleWorld/SimpleWorld" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch  map_file:=/home/nvidia/catkin_ws/src/World/SimpleWorld/simple_world_map.yaml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 15
xterm -e "rosrun add_markers add_markers" &
sleep 5
xterm -e "rosrun pick_objects pick_objects" &
