#include "ros/ros.h"
#include "turtle_control_pkg/TurtleSpeed.h"  // 自定义消息：线速度
#include "geometry_msgs/Twist.h"        // 标准Twist消息类型（线速度+角速度）

// 全局参数（通过ROS参数服务器配置）
double angular_speed;       // 角速度（弧度/秒）
double trajectory_radius;   // 运动轨迹半径

// 全局发布者
ros::Publisher cmd_pub;

// 回调函数：当接收到自定义速度消息时触发
// 参数msg：指向TurtleSpeed消息的常量指针（避免消息被意外修改）
void turtleSpeedCallback(const turtle_control_pkg::TurtleSpeed::ConstPtr& msg) {
    geometry_msgs::Twist cmd;
    cmd.linear.x = msg->linear_speed;  // 从自定义消息中获取线速度，赋值给Twist的x轴（前进方向）
    cmd.angular.z = angular_speed;      // 将全局变量中的角速度赋值给Twist的z轴（旋转方向）

    cmd_pub.publish(cmd);  // 发布控制指令
    ROS_DEBUG("发布指令: 线速度=%.2f, 角速度=%.2f", cmd.linear.x, cmd.angular.z);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_control_node");
    ros::NodeHandle nh;

  
    // 从参数服务器获取角速度（带默认值）
    if (!nh.getParam("turtle_angular_speed", angular_speed)) {
        angular_speed = 0.5;  // 默认值
        ROS_WARN("未找到参数 turtle_angular_speed，使用默认值 %.2f", angular_speed);
    }

   
    cmd_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe("turtle_speed_topic", 10, turtleSpeedCallback);

    // 输出信息日志：提示节点已启动，等待接收速度指令
    ROS_INFO("节点已启动，等待速度指令...");
    ros::spin();  // 进入事件循环
    return 0;
}
