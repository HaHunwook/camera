#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>

class cameraON
{
    ros::NodeHandle nh;
    ros::Subscriber image_sub;
    public:
        cameraON()//생성자
        {
            image_sub = nh.subscribe("/usb_cam/image_raw", 1, &cameraON::cam_start_Callback, this);
        }
        ~cameraON()
        {

        }
        void cam_start_Callback(const sensor_msgs::ImageConstPtr& msg)
        {
            cv::imshow("camera", cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image);
            cv::waitKey(5);            
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cam_sub");
    cameraON ic;
    ros::spin();
    return 0;
}