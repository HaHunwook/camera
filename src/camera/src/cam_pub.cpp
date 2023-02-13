#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("usb_cam/image_raw", 1);

  cv::VideoCapture cam(0);
  cv::Mat data;
  sensor_msgs::ImagePtr msg;
  while (nh.ok())
  {
    cam >> data;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", data).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
  }
}