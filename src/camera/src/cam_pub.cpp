#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh); //이미지 형태 변환
  image_transport::Publisher pub = it.advertise("usb_cam/image", 1);

  cv::VideoCapture cap(0);
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;
  while (nh.ok())
  {
    cap >> frame;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
  }
}