#include <ros/ros.h>
#include "ros/package.h"
#include <cm_transport/Packet.h>

#include <message_transport/message_transport.h>


void callback(const cm_transport::PacketConstPtr& msg)
{
    std::cout << "[Rec]: Now received packet with timestamp "  << std::fixed << std::setprecision(3) << msg->header.stamp.toSec() << std::endl;
    std::cout << "[Rec]: Packet gives you a msg: " << msg->test << std::endl;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "packet_subscriber");
    ros::NodeHandle nh_("~"); // LOCAL


    //refer to the definition in cm_plugins.xml: raw_cm, bz2_cm
    std::string transport = std::string((argc > 1) ? argv[1] : "cm_transport/bz2_cm"); 
    message_transport::MessageTransport<cm_transport::Packet> it(nh_,"cm_transport","cm_transport::Packet");
    message_transport::Subscriber bz2_sub = it.subscribe("/test_tp", 5, callback, transport);

    ros::spin();
    return 0;
}