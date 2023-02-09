#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // 명령줄 매개 변수를 정수로 변환하기 위해

int main(int argc, char** argv)
{
  // 비디오 소스가 매개 변수로 전달되었는지 확인합니다
  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "cam_pub");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  // 비디오 장치에 대해 전달된 명령줄 매개 변수 인덱스를 정수로 변
  std::istringstream video_sourceCmd(argv[1]);
  int video_source;
  // 숫자가 맞는지 확인합니다
  if(!(video_sourceCmd >> video_source)) return 1;

  cv::VideoCapture cap(video_source);
  // 지정된 인덱스로 비디오 장치를 열 수 있는지 확인하십시오
  if(!cap.isOpened()) return 1;
  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // 캡처된 프레임이 실제로 일부 콘텐츠로 가득 차 있는지 확인
    if(!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
      cv::waitKey(1);
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
}