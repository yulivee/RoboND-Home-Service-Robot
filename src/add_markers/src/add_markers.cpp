#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

const float initial_x = -1.7;
const float initial_y = -0.5;
const float goal_x = 5.1;
const float goal_y = 1.5;

enum goalState {
    TOWARDS_GOAL = 0,
    AT_GOAL,
    TOWARDS_INITIAL,
    AT_INITIAL
};

goalState state = TOWARDS_GOAL;

visualization_msgs::Marker init_marker() {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    marker.ns = "add_markers";
    marker.id = 0;

    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = goal_x;
    marker.pose.position.y = goal_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.08;
    marker.scale.y = 0.08;
    marker.scale.z = 0.23;

    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    return marker;
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    // ROS_INFO("I received odom: [%f,%f]", odom->pose.pose.position.y, odom->pose.pose.position.x); //store x,y,z position values

    float curPoseX = odom->pose.pose.position.x;
    float curPoseY = odom->pose.pose.position.y;
    if ( state == TOWARDS_GOAL &&
            ( curPoseX <= goal_x + 0.2 && curPoseX >= goal_x - 0.2 ) &&
            ( curPoseY <= goal_y + 0.2 && curPoseY >= goal_y - 0.2 )
       ) {
        state = AT_GOAL;
        ROS_WARN("arrived at goal position [%f, %f]", curPoseX, curPoseY);
    }

    if ( state == TOWARDS_INITIAL &&
            ( curPoseX <= initial_x + 0.2 && curPoseX >= initial_x - 0.2 ) &&
            ( curPoseY <= initial_y + 0.2 && curPoseY >= initial_y - 0.2 )
       ) {
        state = AT_INITIAL;
        ROS_WARN("arrived at dropoff position [%f, %f]", curPoseX, curPoseY);
    }
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber odom_sub = n.subscribe("/odom", 100, odomCallback);


    visualization_msgs::Marker marker = init_marker();

    while (ros::ok())
    {

        while ( marker_pub.getNumSubscribers() < 1 )
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }

        ROS_WARN_ONCE("Successfully found a subscriber");

        ros::spinOnce();

        switch (state) {
        case TOWARDS_GOAL:
        {
            // Do nothing
            break;
        }
        case AT_GOAL:
        {
            marker.color.a = 0.0;
            marker.pose.position.x = initial_x;
            marker.pose.position.y = initial_y;
            marker_pub.publish(marker);
            sleep(5);
            state = TOWARDS_INITIAL;
            ROS_ERROR("removing marker");
            break;
        }
        case TOWARDS_INITIAL:
        {
            marker.color.a = 1.0;
            break;
        }
        case AT_INITIAL:
        {
            marker.color.a = 0.0;

            break;
        }
        default:
        {
            break;
        }
        }

        marker_pub.publish(marker);

        r.sleep();

    }
}
