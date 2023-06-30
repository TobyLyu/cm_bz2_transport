#!/usr/bin/env python

import roslib
import rospy

from sensor_msgs.msg import CompressedImage
import numpy as np
import cv2
# from scipy.ndimage import filters



def republish(ros_data):
    global pub
    np_arr = np.fromstring(ros_data.data, np.uint8)
    image_np = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    msg = CompressedImage()
    msg.header.stamp = ros_data.header.stamp
    msg.format = "jpeg"
    msg.data = np.array(cv2.imencode('.jpg', image_np)[1]).tostring()
    pub.publish(msg)


if __name__ == '__main__':
    global pub
    rospy.init_node('republisher', anonymous=True)
    sub = rospy.Subscriber("/its1/usb_cam/usb_cam_1/compressed", CompressedImage, republish, queue_size = 2000)
    pub = rospy.Publisher("/its1/usb_cam/usb_cam_1/republished/compressed", CompressedImage, queue_size = 1)
    rospy.spin()

