#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

class cam
{
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Subscriber image_sub;
    public:
        cam(): it(nh)
        {
            image_sub = it.subscribe("usb_cam/image_raw", 1, &cam::imageCallback, this);
        }
        ~cam()
        {

        }
        void imageCallback(const sensor_msgs::ImageConstPtr& msg)
        {
            cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
            cv::waitKey(1);            
        }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_sub");
    cam ic;
    ros::spin();
}