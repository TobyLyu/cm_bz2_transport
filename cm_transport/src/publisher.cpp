#include <ros/ros.h>
#include "ros/package.h"
#include <cm_transport/Packet.h>
#include <std_msgs/Header.h>
#include <sensor_msgs/Image.h>

#include <message_transport/message_transport.h>

// #include <pluginlib/class_loader.hpp>

message_transport::Publisher bz2_pub_;
sensor_msgs::Image image, empty_image;

void image_callback(const sensor_msgs::ImageConstPtr& msg)
{
    image = *msg;
}

void timer_callback(const ros::TimerEvent&)
{
    cm_transport::Packet::Ptr packet (new cm_transport::Packet);

    packet->header.stamp = ros::Time::now();
    packet->test = "Hi~!";
    packet->image = image;

    std::cout << "[Pub]: Now publishing packet with timestamp " << std::fixed << std::setprecision(3) << packet->header.stamp.toSec() << std::endl;
    bz2_pub_.publish(*packet);

    image = empty_image;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "packet_publisher");
    ros::NodeHandle nh_("~"); // LOCAL

    ros::Subscriber image_sub = nh_.subscribe("/usb_cam/image_raw", 1, image_callback);

    message_transport::MessageTransport<cm_transport::Packet> it_(nh_,"cm_transport","cm_transport::Packet");      
    bz2_pub_ = it_.advertise("/test_tp", 10);

    ros::Timer timer1 = nh_.createTimer(ros::Duration(1.0 / 30.0), timer_callback);

    ros::spin();      
    return 0;
}