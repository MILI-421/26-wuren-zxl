#include <ros/ros.h>
#include <fsd_common_msgs/ConeDetections.h>

// 全局变量
int g_red   = 0;
int g_blue  = 0; 


void count_callback(const fsd_common_msgs::ConeDetections::ConstPtr& msg)
{
    for (const auto& cone : msg->cone_detections)   // 遍历每一个锥桶，指针指向cone_detections
    {
        const std::string& color = cone.color.data; // 统计各颜色锥桶个数
        if (color == "r")
            ++g_red;
        else if (color == "b")
            ++g_blue;
    }
    
    ROS_INFO("Current count - red=%d, blue=%d", g_red, g_blue);
    
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"count_cones");

    ros::NodeHandle nh;

    ros::Subscriber sub=nh.subscribe("/perception/lidar/cone_side",1000,count_callback);


    ros::spin();

    // 输出最终统计结果
    ROS_INFO("Final count - red=%d, blue=%d", g_red, g_blue);

    return 0;
}
