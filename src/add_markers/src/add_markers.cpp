#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    uint32_t shape = visualization_msgs::Marker::CYLINDER;

    while (ros::ok())
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "/map";
        marker.header.stamp = ros::Time::now();

        marker.ns = "add_markers";
        marker.id = 0;

        marker.type = shape;

        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = 5.1;
        marker.pose.position.y = 1.5;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 0.0275;
        marker.scale.y = 0.0275;
        marker.scale.z = 0.23;

        marker.color.r = 0.5f;
        marker.color.g = 1.0f;
        marker.color.b = 0.5f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();

        while ( marker_pub.getNumSubscribers() < 1 )
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }
        marker_pub.publish(marker);

        r.sleep();

        sleep(5);

        marker.color.a = 0.0;
        marker_pub.publish(marker);

        sleep(5);

        marker.pose.position.x = -1.7;
        marker.pose.position.y = -0.5;
        marker.pose.position.z = 0;
        marker_pub.publish(marker);
    }
}
