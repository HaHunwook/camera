#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>//윈도우 화면, UI처리 및 마우스 제어 가능
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cam_pub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub;
    image_pub = it.advertise("/usb_cam/image_raw", 1);
    sensor_msgs::Image::ConstPtr msg;
    // msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    while(ros::ok())
    {
        image_pub.publish(msg);
        ros::spinOnce();
    }
    return 0;
}