#include <ros/ros.h>
#include "ros/package.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
// #include <opencv4/opencv2/core.hpp>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <stdio.h>

using namespace std;
using namespace cv;

string right_tp_str, left_tp_str;

cv::Mat R_mat = (cv::Mat_<double>(3,3) << 0.4275380147338123, 0.03871046209741896, -0.9031681715393179, 0.005268427834524487, 0.9989590784699285, 0.04531007846675674, 0.9039820184194057, -0.024130057329304767, 0.4268890379333505);
cv::Mat T_mat = (cv::Mat_<double>(3,1) << -0.03689947841790725, 0.002085564233768624, -0.02171739566600771);

cv::Mat cam_right_mat = (cv::Mat_<double>(3,3) << 609.2520980862241, 0.0, 561.6798098202845, 0.0, 625.4919316399147, 348.0194810542202, 0.0, 0.0, 1.0);
cv::Mat cam_left_mat = (cv::Mat_<double>(3,3) << 619.0755112126609, 0.0, 660.6434968110426, 0.0, 630.1231258440725, 391.09836325008297, 0.0, 0.0, 1.0);

cv::Mat right_proj_mat = (cv::Mat_<double>(3,4) << 67008.00844976233, 0.0, -25589.350172042847, -2872.4218806696545, 0.0, 67008.00844976233, 3176.3079147338867, 0.0, 0.0, 0.0, 1.0, 0.0);
cv::Mat left_proj_mat = (cv::Mat_<double>(3,4) << 67008.00844976233, 0.0, -25589.350172042847, 0.0, 0.0, 67008.00844976233, 3176.3079147338867, 0.0, 0.0, 0.0, 1.0, 0.0);

cv::Mat homography_mat_r2l, homography_mat_l2r;

void callback(const sensor_msgs::ImageConstPtr& img_right_msg, const sensor_msgs::ImageConstPtr& img_left_msg)
{
    cv_bridge::CvImagePtr cv_right_ptr, cv_left_ptr;
    try
    {
      cv_right_ptr = cv_bridge::toCvCopy(img_right_msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    try
    {
      cv_left_ptr = cv_bridge::toCvCopy(img_left_msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    cv::Mat img_right, img_left;
    img_right = cv_right_ptr->image.clone();
    img_left = cv_left_ptr->image.clone();
    
    cv::Mat WarpImg, DstImg;
    warpPerspective(img_right, WarpImg, homography_mat_r2l, cv::Size(img_right.cols + img_left.cols, img_right.rows));
	cv::imshow("透视变换", WarpImg);

	DstImg = WarpImg.clone();
	//将img_left拷贝到透视变换后的图片上，完成图像拼接
	img_left.copyTo(DstImg(cv::Rect(0, 0, img_left.cols, img_left.rows)));
	cv::imshow("图像全景拼接", DstImg);

    cv::waitKey(10);
    return;

}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "stereo_fusion");
    ros::NodeHandle priv_nh("~");

    priv_nh.getParam("img_right_tp", right_tp_str);
    priv_nh.getParam("img_left_tp", left_tp_str);
    cout << "img_right_tp: " << right_tp_str << endl;
    cout << "img_left_tp: " << left_tp_str << endl;
    

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image,sensor_msgs::Image> mySyncPolicy;

    message_filters::Subscriber<sensor_msgs::Image>* img_right_sub_;   // topic1 输入
    message_filters::Subscriber<sensor_msgs::Image>* img_left_sub_;   // topic2 输入
    message_filters::Synchronizer<mySyncPolicy>* sync_;

    img_right_sub_ = new message_filters::Subscriber<sensor_msgs::Image>(priv_nh, right_tp_str, 1);
    img_left_sub_  = new message_filters::Subscriber<sensor_msgs::Image>(priv_nh, left_tp_str, 1);
    
    sync_ = new  message_filters::Synchronizer<mySyncPolicy>(mySyncPolicy(10), *img_right_sub_, *img_left_sub_);
    sync_->registerCallback(boost::bind(&callback, _1, _2));

    homography_mat_r2l = cam_left_mat * R_mat * cam_right_mat.inv(); // right to left?
    // homography_mat_l2r = cam_right_mat * R_mat * cam_left_mat.inv(); // left to right?

    ros::Rate loop_rate(30);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::shutdown();
    return 0;  

}