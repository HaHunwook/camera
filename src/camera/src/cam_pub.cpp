#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>
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
    while(ros::ok())
    {
        image_pub.publish(msg);
        ros::spinOnce();
    }
    return 0;
}