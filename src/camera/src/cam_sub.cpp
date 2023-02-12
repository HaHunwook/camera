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
        // void cam_start_Callback(const std_msgs::String::ConstPtr& msg)
        // {
        //     ROS_INFO("%d",image_sub);
        //     cv_bridge::CvImagePtr cv_ptr;
        //     cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        //     cv::imshow("Image window",cv_ptr->image);
        //     cv::waitKey(3);
        // }
        void cam_start_Callback(const sensor_msgs::ImageConstPtr& msg)
        {
            cv::imshow("camera", cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image);
            //이미지쇼함수(창의 이름, 불러올 이미지가 저장된 Mat형식)이지만
            //캠을 통해서 실시간으로 이미지를 호출하기 위해서
            //센서메시지 이미지 메시지를 OpenCV호환 toCvShar: 이미지 데이터 공유
            //이미지 데이터를 파랑-초록-레드 순의 컬러이미지 인코딩
            //인코딩 한 메시지를 image라는 OpenCV의 포인터 변수에 간접적으로 접근
            //회색으로 하고싶으면 momo8을 사용(8비트의 회색 이미지)
            cv::waitKey(5);
            //1000은 1초 동안 대기, 이유 imshow함수를 보기 위해서, 이유: 영상이기 때문에 프레임을 올리기 위함
        }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cam_sub");
    cameraON ic;
    ros::spin();
    return 0;
}