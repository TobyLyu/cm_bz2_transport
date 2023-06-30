# cm_bz2_transport
 
This is a BZ2 lossless compression package integrated with the USB camera driver as an example.

You can modify the contents of Packet.msg for your application (but don't change the filename!)

The BZ2 publisher will create two topics, one is raw ('/test_tp'), one is bz2 ('/test_tp/bz2'). Only when bz2 topic is subscribed, the bz2 compression is actual running.

BZ2 is not suitable for small msg compression. It will increase the msg size!

Examples of Publisher and Subscriber are given. 

    rosrun cm_transport cm_transport_publisher
    rosrun cm_transport cm_transport_subscriber

You will find that before launching the usb driver, the size after compress increases. 

    [Pub]: Now publishing packet with timestamp 1688116543.813
    Message compression: from 61 to 71 bytes
    [Pub]: Now publishing packet with timestamp 1688116543.847
    Message compression: from 61 to 67 bytes
    [Pub]: Now publishing packet with timestamp 1688116543.880
    Message compression: from 61 to 66 bytes

After launching the usb camera
    roslaunch usb_cam usb_cam.launch

Compression becomes normal:

    [Pub]: Now publishing packet with timestamp 1688116630.059
    Message compression: from 691272 to 425654 bytes
    [Pub]: Now publishing packet with timestamp 1688116630.094
    Message compression: from 691272 to 426954 bytes
    [Pub]: Now publishing packet with timestamp 1688116630.128
    Message compression: from 691272 to 426723 bytes