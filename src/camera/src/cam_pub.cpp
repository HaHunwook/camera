#include <ros/ros.h>
#include <image_transport/image_transport.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  ROS_INFO("hh");
}
int main(int argc,char** argv)
{
    ros::init(argc,argv,"turtle_drive");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("in_image_base_topic", 1, imageCallback);
    image_transport::Publisher pub = it.advertise("out_image_base_topic", 1);
}