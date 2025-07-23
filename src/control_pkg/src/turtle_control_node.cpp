#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "tur_msgs/lir.h"

ros::Publisher cmd;  // 声明发布者对象

double turtle_angular;       // 角速度（弧度/秒）
double turtle_radius;   // 运动轨迹半径


void control_callback(const tur_msgs::lir::ConstPtr& msg)
{
    geometry_msgs::Twist cmd_msg;
    cmd_msg.linear.x=msg->turtle_linear; //从自定义消息中获取线速度，赋值给Twist的x轴
    cmd_msg.angular.z=turtle_angular;  //将全局变量中的角速度赋值给Twist的z轴 
    cmd.publish(cmd_msg); //发布控制指令
    ROS_INFO("发布指令: 线速度=%.2f, 角速度=%.2f", 
             cmd_msg.linear.x, cmd_msg.angular.z); 
}    

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"turtle_control_node");

    ros::NodeHandle nh;

   // 从参数服务器读取 YAML 中的固定参数
    nh.param<double>("turtle_angular", turtle_angular, 0.5);  // 默认值 0.5
    nh.param<double>("turtle_radius", turtle_radius, 1.0); 
    ROS_INFO("从参数服务器读取 turtle_angular = %.2f", turtle_angular);
    ROS_INFO("从参数服务器读取 turtle_radius = %.2f", turtle_radius);
    // 发布 /turtle1/cmd_vel
    cmd = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Subscriber sub=nh.subscribe("lir_data",10,control_callback);

    while(ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
    
}

