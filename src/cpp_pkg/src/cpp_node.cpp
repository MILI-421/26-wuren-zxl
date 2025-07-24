#include <ros/ros.h>   // ROS节点初始化、订阅发布等核心功能
#include <fsd_common_msgs/ConeDetections.h>    // 锥桶检测消息类型（自定义）
#include <sensor_msgs/Image.h>  // ROS图像消息类型（用于发布结果）
#include <cv_bridge/cv_bridge.h>   // OpenCV图像与ROS图像的转换工具

#include <opencv2/opencv.hpp>

#include <Eigen/Dense>
#include <string>
#include <eigen_conversions/eigen_msg.h>  // 包含 eigen_conversions 头文件

// 全局发布器：用于发布投影后的图像消息（避免在回调函数中重复创建）
ros::Publisher pub;

//相机内参矩阵（3×3，const修饰确保不可修改）：将相机坐标系转换为像素坐标系
const Eigen::Matrix3d intrinsic = (Eigen::Matrix3d() <<
    532.795, 0.0,      632.15,                // 第1行：fx（x轴焦距）、0、cx（x轴主点）
    0.0,     532.72,   363.428,                // 第2行：0、fy（y轴焦距）、cy（y轴主点）
    0.0,     0.0,      1.0).finished();      // 第3行：齐次坐标归一化参数

// 相机外参矩阵（3×4，const修饰）：将雷达坐标系转换为相机坐标系
const Eigen::Matrix<double, 3, 4> extrinsic = (Eigen::Matrix<double, 3, 4>() <<
     3.5594209875121074e-03, -9.9987761481865733e-01, -1.5234365979146680e-02, 8.9277270417879417e-02,            // 第1行：旋转+平移分量
     1.9781062410225703e-03,  1.5241472820252011e-02, -9.9988188532544631e-01, 9.1100499695349946e-01,            // 第2行：旋转+平移分量
     9.9999170877459420e-01,  3.5288653732390984e-03,  2.0321149683686368e-03, 1.9154049062915668e+00).finished(); // 第3行：旋转+平移分量

// 回调函数：当订阅的锥桶消息到达时触发，处理数据并生成投影图像
void coneCallback(const fsd_common_msgs::ConeDetections::ConstPtr& msg)
{   
    // 创建空白图像：尺寸360（高）×1280（宽），3通道8位无符号整数，初始为白色（BGR格式）
    cv::Mat img(360, 1280, CV_8UC3, cv::Scalar(255, 255, 255));

    for (const auto& cone : msg->cone_detections)
    {
        // 1. 雷达坐标
        Eigen::Vector4d radar(cone.position.x, cone.position.y, cone.position.z, 1.0);

        // 2. 投影
        Eigen::Vector3d pxh = intrinsic * extrinsic * radar;
        
        // 透视除法：转换为像素坐标（u,v），+0.5用于四舍五入取整
        int u = static_cast<int>(pxh(0) / pxh(2) + 0.5);
        int v = static_cast<int>(pxh(1) / pxh(2) + 0.5);
        ROS_INFO("锥桶投影坐标：u=%d, v=%d", u, v);  // 新增：打印坐标
       // 3.越界检查
        if (u < 0 || u >= 1280 || v < 0 || v >= 360) {
           ROS_WARN("锥桶坐标越界：u=%d, v=%d", u, v);  // 新增：越界警告
           continue;
        }

        // 4. 颜色 
        cv::Scalar color;
        if (cone.color.data == "yellow")      color = cv::Scalar(0, 255, 255);
        else if (cone.color.data == "blue")   color = cv::Scalar(255, 0, 0);
        else                             color = cv::Scalar(0, 0, 255);   // 默认红

        cv::circle(img, cv::Point(u, v), 5, color, -1);
    }

    // 5. 发布
    pub.publish(cv_bridge::CvImage(msg->header, "bgr8", img).toImageMsg());
}

// 主函数：初始化节点，创建订阅器和发布器
int main(int argc, char** argv)
{
    ros::init(argc, argv, "cpp_node");
    ros::NodeHandle nh;

    // 初始化发布器：发布话题"/projected_image"，消息类型sensor_msgs::Image，队列长度10
    pub = nh.advertise<sensor_msgs::Image>("/projected_image", 10);

    ros::Subscriber sub = nh.subscribe("/perception/fusion/cone_fusion", 10, coneCallback);

    // 进入ROS事件循环：持续等待消息并调用回调函数
    ros::spin();
    return 0;
}
