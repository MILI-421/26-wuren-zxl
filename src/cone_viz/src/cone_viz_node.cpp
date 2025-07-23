#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <fsd_common_msgs/ConeDetections.h> 

ros::Publisher marker_pub;  // 声明一个发布者变量，用于发布可视化标记消息
/*
    ros::Publisher：ROS 中的发布者类型，用于向某个话题发布消息
    marker_pub：变量名，后续会绑定到/viz/cones话题
*/

void coneCallback(const fsd_common_msgs::ConeDetections::ConstPtr& msg) { //ConstPtr&：常量指针引用，确保消息不被修改，同时高效传递数据
    visualization_msgs::MarkerArray marker_array;  // 创建一个MarkerArray对象，用于存储多个标记

    /*
    for循环：遍历消息中所有检测到的锥桶
    msg->cone_detections：从接收到的消息中获取锥桶数组（所有检测到的锥桶都存在这里）
    size()：获取锥桶数量，循环次数等于锥桶数量
    i：循环索引，用于区分不同锥桶

    const auto& cone：用auto自动推断类型，cone指代当前遍历的锥桶
    msg->cone_detections[i]：第 i 个锥桶的具体数据（位置、颜色等
    */
    for (size_t i = 0; i < msg->cone_detections.size(); ++i) {  // 遍历检测到的锥桶
        const auto& cone = msg->cone_detections[i];  // 取出当前锥桶的属性
        visualization_msgs::Marker marker;  // 声明一个可视化标记变量
        marker.header = msg->header;  // 包含正确的 frame_id 和时间戳
        marker.ns = "cones";  // 命名空间
        marker.id = i;  // 标记 ID
        marker.type = visualization_msgs::Marker::CYLINDER;  // 标记类型为圆柱体
        marker.action = visualization_msgs::Marker::ADD;  // 标记动作为添加

        // 设置锥桶位置
        marker.pose.position = cone.position;
        marker.pose.orientation.w = 1.0;  // 无旋转

        // 设置锥桶尺寸（可根据需求调整）
        marker.scale.x = 0.3;
        marker.scale.y = 0.3;
        marker.scale.z = 0.6;

        // 根据颜色标识设置颜色
        if (cone.color.data == "r") {
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;
        } else if (cone.color.data == "b") {
            marker.color.r = 0.0;
            marker.color.g = 0.0;
            marker.color.b = 1.0;
        }
        marker.color.a = 1.0;  // 不透明

        marker.lifetime = ros::Duration(0.5);  // 标记显示时长，避免残留
        marker_array.markers.push_back(marker);
    }
    marker_pub.publish(marker_array);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "cone_viz_node");
    ros::NodeHandle nh;
    marker_pub = nh.advertise<visualization_msgs::MarkerArray>("/viz/cones", 10);
    ros::Subscriber cone_sub = nh.subscribe("/perception/lidar/cone_side", 10, coneCallback);
    ros::spin();
    return 0;
}

