#include <ros/ros.h>
// #include <std_msgs/Header.h>
// #include <templated_transports/declare_all_templates.h>
#include <pluginlib/class_list_macros.h>
#include "bz2_transport/bz2_publisher.h"
#include "bz2_transport/bz2_subscriber.h"
#include <bz2_transport/BZ2Packet.h>
// #include <buffer/CustomMsg.h>

// DECLARE_ALL_TEMPLATES(bz2_transport::BZ2Packet)

PLUGINLIB_EXPORT_CLASS(bz2_transport::BZ2Publisher<bz2_transport::BZ2Packet>, message_transport::PublisherPlugin<bz2_transport::BZ2Packet>)

PLUGINLIB_EXPORT_CLASS(bz2_transport::BZ2Subscriber<bz2_transport::BZ2Packet>, message_transport::SubscriberPlugin<bz2_transport::BZ2Packet>)
