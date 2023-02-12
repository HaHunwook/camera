// #include <ros/ros.h>
// #include <image_transport/image_transport.h>
// #include <cv_bridge/cv_bridge.h>
// #include <sensor_msgs/Image.h>
// #include <opencv2/highgui/highgui.hpp>

// class cameraON
// {
//     ros::NodeHandle nh;
//     ros::Subscriber image_sub;
//     public:
//         cameraON()
//         {
//             image_sub = nh.subscribe("/usb_cam/image_raw", 1, &cameraON::cam_start_Callback, this);
//         }
//         ~cameraON()
//         {

//         }
//         void cam_start_Callback(const sensor_msgs::ImageConstPtr& msg)
//         {
//             cv::imshow("camera", cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image);
//             cv::waitKey(5);            
//         }
// };

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "cam_sub");
//     cameraON ic;
//     ros::spin();
//     return 0;
// }

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
            image_sub = it.subscribe("usb_cam/image", 1, &cam::imageCallback, this);
        }
        ~cam()
        {

        }
        void imageCallback(const sensor_msgs::ImageConstPtr& msg)
        {
            cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
            cv::waitKey(5);            
        }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  cam ic;
  ros::spin();
  cv::destroyWindow("view");
}